#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Tile.h"
using std::string;
using std::vector;
using std::ifstream;

class Board
{
	int _numCols;
	int _numRows;
	int _numMines;
	int _remainingMines;
	bool _gameLost;
	bool _gameWon;
	vector<vector<Tile>> _tiles;
public:
	/*==== Constructor ====*/
	Board(const string& filePath = "boards/config.cfg");

	/*==== Behaviors ====*/
	void MousePress(float& x, float& y);
	void AddAdjacentTile(int adjRowIndex, int adjColIndex);
	void ResetBoard(const string& filePath);
	void DebugRevealMines();
	void DebugUnrevealMines();
	void RevealMines();
	void FlagMines();

	/*==== Check Conditions ====*/
	bool InBoard(int& adjRowIndex, int& adjColIndex) const;
	bool GameWon();

	/*==== Board Setup ====*/
	void Deserialize(ifstream& inFile);
	void CreateBoard();
	void LoadBoardFromFile(const string& filePath);
	void DrawTiles(sf::RenderWindow& window);
	void PlaceMines();
	void SetAdjacentTiles();

	/*==== Accessors ====*/
	const int GetWidth() const;
	const int GetHeight() const;
	const int GetRemainingMines() const;
	const bool IsGameWon() const;
	const bool IsGameLost() const;
};