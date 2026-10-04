#include <string>
#include <vector>
#include "Tile.h"
#include "TextureManager.h"
using namespace std;

/*==== Constructor =====*/
Tile::Tile()
{
	_mineSprite.setTexture(TextureManager::GetTexture("mine"));
	_flagSprite.setTexture(TextureManager::GetTexture("flag"));
	Reset();
}

/*==== Behavior Functions ====*/
bool Tile::Contains(float& x, float& y)
{
	return _tileSprite.getGlobalBounds().contains(x, y);
}
void Tile::Reveal()
{
	_isRevealed = true;
	_tileSprite.setTexture(TextureManager::GetTexture("tile_revealed"));
	if (!_hasMine)
	{
		if (_numAdjacentMines > 0)
			_numSprite.setTexture(TextureManager::GetTexture("number_" + to_string(_numAdjacentMines)));
		else
			RevealAdjacentTiles();
	}
}
void Tile::ToggleFlag()
{
	_hasFlag = !_hasFlag;
}
void Tile::ToggleMine()
{
	_mineRevealed = !_mineRevealed;
}
void Tile::Reset()
{
	_tileSprite.setTexture(TextureManager::GetTexture("tile_hidden"));
	_isRevealed = false;
	_hasMine = false;
	_hasFlag = false;
	_mineRevealed = false;
	ClearAdjacentTiles();
}
void Tile::RevealAdjacentTiles()
{
	if (_numAdjacentMines == 0 || _hasMine)
	{
		for (unsigned int i = 0; i < _adjacentTiles.size(); i++)
		{
			if (!_adjacentTiles[i]->IsRevealed() && !_adjacentTiles[i]->HasMine() && !_adjacentTiles[i]->HasFlag())
			{
				_adjacentTiles[i]->Reveal();
				_adjacentTiles[i]->RevealAdjacentTiles();
			}
		}
	}
}
void Tile::ClearAdjacentTiles()
{
	_adjacentTiles.clear();
	_numAdjacentMines = 0;
}

/*==== Mutator Functions ====*/
void Tile::SetMine(bool hasMine)
{
	_hasMine = hasMine;
}
void Tile::SetPosition(float x, float y)
{
	_tileSprite.setPosition(x, y);
	_mineSprite.setPosition(x, y);
	_flagSprite.setPosition(x, y);
	_numSprite.setPosition(x, y);
}
void Tile::AddAdjacentTile(Tile* neighbor)
{
	_adjacentTiles.push_back(neighbor);
	if (neighbor->HasMine())
		_numAdjacentMines++;
}

/*==== Accessor Functions ====*/
const sf::Sprite& Tile::GetTileSprite() const
{
	return _tileSprite;
}
const sf::Sprite& Tile::GetMineSprite() const
{
	return _mineSprite;
}
const sf::Sprite& Tile::GetFlagSprite() const
{
	return _flagSprite;
}
const sf::Sprite& Tile::GetNumSprite() const
{
	return _numSprite;
}
bool Tile::IsRevealed() const
{
	return _isRevealed;
}
bool Tile::MineRevealed() const
{
	return _mineRevealed;
}
bool Tile::HasMine() const
{
	return _hasMine;
}
bool Tile::HasFlag() const
{
	return _hasFlag;
}
int Tile::GetNumAdjacentMines() const
{
	return _numAdjacentMines;
}