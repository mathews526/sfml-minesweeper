#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "Board.h"
#include "Random.h"
using namespace std;

/*==== Constructor ====*/
Board::Board(const string& filePath) : _gameLost(false), _gameWon(false), _isFirstClick(true)
{
	ifstream configFile(filePath);
	Deserialize(configFile);
	CreateBoard();
}

/*==== Behavior Functions ====*/
void Board::MousePress(float& x, float& y)
{
	if (!_gameWon && !_gameLost)
	{
		for (unsigned int row = 0; row < _tiles.size(); row++)
		{
			for (unsigned int col = 0; col < _tiles[row].size(); col++)
			{
				Tile& tile = _tiles[row][col];
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (tile.Contains(x, y) && !tile.HasFlag())
					{
						if (_isFirstClick)
						{
							PlaceMines(row, col);
							SetAdjacentTiles();
							_isFirstClick = false;
						}
						
						tile.Reveal();

						if (tile.HasMine())
						{
							_gameLost = true;
							DebugUnrevealMines();
							RevealMines();
						}
						else if (GameWon())
						{
							_gameWon = true;
							DebugUnrevealMines();
							FlagMines();
						}
					}
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					if (tile.Contains(x, y))
					{
						tile.ToggleFlag();

						if (tile.HasFlag())
							_remainingMines--;
						else
							_remainingMines++;
					}
				}
			}
		}
	}
}
void Board::AddAdjacentTile(int row, int col)
{
	Tile& currentTile = _tiles[row][col];
	int adjRowIndex = 0;
	int adjColIndex = 0;
	for (int vertical = -1; vertical <= 1; vertical++)
	{
		for (int horizontal = -1; horizontal <= 1; horizontal++)
		{
			if (vertical == 0 && horizontal == 0)
				continue;

			adjRowIndex = row + vertical;
			adjColIndex = col + horizontal;

			if (InBoard(adjRowIndex, adjColIndex))
				currentTile.AddAdjacentTile(&_tiles[adjRowIndex][adjColIndex]);
		}
	}
}
void Board::ResetBoard(const string& filePath)
{
	_tiles.clear();
	_tiles.resize(_numRows, vector<Tile>(_numCols));

	ifstream configFile(filePath);
	Deserialize(configFile);
	CreateBoard();
	_remainingMines = _numMines;
	_gameLost = false;
	_gameWon = false;
	_isFirstClick = true;

	for (unsigned int row = 0; row < _tiles.size(); row++)
	{
		for (unsigned int col = 0; col < _tiles[row].size(); col++)
			_tiles[row][col].Reset();
	}
}
void Board::DebugRevealMines()
{
	if (!_gameLost && !_gameWon)
	{
		for (unsigned int row = 0; row < _tiles.size(); row++)
		{
			for (unsigned int col = 0; col < _tiles[row].size(); col++)
			{
				if (_tiles[row][col].HasMine())
					_tiles[row][col].ToggleMine();
			}
		}
	}
}
void Board::DebugUnrevealMines()
{
	for (unsigned int row = 0; row < _tiles.size(); row++)
	{
		for (unsigned int col = 0; col < _tiles[row].size(); col++)
		{
			if (_tiles[row][col].MineRevealed())
				_tiles[row][col].ToggleMine();
		}
	}
}
void Board::RevealMines()
{
	for (unsigned int row = 0; row < _tiles.size(); row++)
	{
		for (unsigned int col = 0; col < _tiles[row].size(); col++)
		{
			if (_tiles[row][col].HasMine())
				_tiles[row][col].Reveal();
		}
	}
}
void Board::FlagMines()
{
	for (unsigned int row = 0; row < _tiles.size(); row++)
	{
		for (unsigned int col = 0; col < _tiles[row].size(); col++)
		{
			if (_tiles[row][col].HasMine() && !_tiles[row][col].HasFlag())
			{
				_tiles[row][col].ToggleFlag();
				_remainingMines--;
			}
		}
	}
}

/*==== Check Condition Functions ====*/
bool Board::InBoard(int& adjRowIndex, int& adjColIndex) const
{
	if (adjRowIndex >= 0 && adjColIndex >= 0 && adjRowIndex < _numRows && adjColIndex < _numCols)
		return true;
	return false;
}
bool Board::GameWon()
{
	for (unsigned int row = 0; row < _tiles.size(); row++)
	{
		for (unsigned int col = 0; col < _tiles[row].size(); col++)
		{
			if (!_tiles[row][col].HasMine() && !_tiles[row][col].IsRevealed())
				return false;
		}
	}
	return true;
}

/*==== Board Setup Functions ====*/
void Board::Deserialize(ifstream& inFile)
{
	string lineFromFile;
	getline(inFile, lineFromFile);
	_numCols = stoi(lineFromFile);

	getline(inFile, lineFromFile);
	_numRows = stoi(lineFromFile);

	getline(inFile, lineFromFile);
	_numMines = stoi(lineFromFile);

	_remainingMines = _numMines;
}
void Board::CreateBoard()
{
	_tiles.resize(_numRows, vector<Tile>(_numCols));

	for (unsigned int row = 0; row < _tiles.size(); row++)
	{
		for (unsigned int col = 0; col < _tiles[row].size(); col++)
			_tiles[row][col].SetPosition(col * 32.0f, row * 32.0f);
	}
}
void Board::LoadBoardFromFile(const string& filePath)
{
	ifstream inFile("boards/" + filePath + ".brd");

	_tiles.clear();
	_tiles.resize(_numRows, vector<Tile>(_numCols));
	CreateBoard();
	_gameLost = false;
	_gameWon = false;
	_numMines = 0;

	for (unsigned int row = 0; row < _tiles.size(); row++)
	{
		for (unsigned int col = 0; col < _tiles[row].size(); col++)
			_tiles[row][col].Reset();
	}
	_isFirstClick = false; // Custom boards already have fixed mine placements

	string lineFromFile;
	int row = 0;
	while (getline(inFile, lineFromFile))
	{
		for (unsigned int col = 0; col < _tiles[row].size(); col++)
		{
			if (lineFromFile[col] == '1')
			{
				_tiles[row][col].SetMine(true);
				_numMines++;
			}
		}
		row++;
	}
	_remainingMines = _numMines;
	SetAdjacentTiles();
}
void Board::DrawTiles(sf::RenderWindow& window)
{
	for (unsigned int row = 0; row < _tiles.size(); row++)
	{
		for (unsigned int col = 0; col < _tiles[row].size(); col++)
		{
			Tile& tile = _tiles[row][col];
			window.draw(tile.GetTileSprite());

			if (tile.IsRevealed())
			{
				if (tile.HasMine())
					window.draw(tile.GetMineSprite());
				else
					window.draw(tile.GetNumSprite());
				if (tile.HasFlag() && _gameLost)
				{
					window.draw(tile.GetFlagSprite());
					window.draw(tile.GetMineSprite());
				}
			}
			else
			{
				if (tile.HasFlag())
					window.draw(tile.GetFlagSprite());
				if (tile.MineRevealed() && tile.HasMine())
					window.draw(tile.GetMineSprite());
			}
		}
	}
}
void Board::PlaceMines(int firstRow, int firstCol)
{
	int minesPlaced = 0;
	while (minesPlaced < _numMines)
	{
		int row = Random::Int(0, _numRows - 1);
		int col = Random::Int(0, _numCols - 1);

		if ((row == firstRow && col == firstCol) || _tiles[row][col].HasMine())
			continue;

		_tiles[row][col].SetMine(true);
		minesPlaced++;
	}
}
void Board::SetAdjacentTiles()
{
	for (unsigned int row = 0; row < _tiles.size(); row++)
	{
		for (unsigned int col = 0; col < _tiles[row].size(); col++)
		{
			_tiles[row][col].ClearAdjacentTiles();
			AddAdjacentTile(row, col);
		}
	}
}

/*==== Accessor Functions ====*/
const int Board::GetWidth() const
{
	return _numCols * 32;
}
const int Board::GetHeight() const
{
	return (_numRows * 32) + 100;
}
const int Board::GetRemainingMines() const
{
	return _remainingMines;
}
const bool Board::IsGameWon() const
{
	return _gameWon;
}
const bool Board::IsGameLost() const
{
	return _gameLost;
}