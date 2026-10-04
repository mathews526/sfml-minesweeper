#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using std::vector;

class Tile
{
	sf::Sprite _tileSprite;
	sf::Sprite _mineSprite;
	sf::Sprite _flagSprite;
	sf::Sprite _numSprite;
	bool _isRevealed;
	bool _hasMine;
	bool _hasFlag;
	bool _mineRevealed;
	int _numAdjacentMines;
public:
	vector<Tile*> _adjacentTiles;
	/*==== Constructor ====*/
	Tile();

	/*==== Behaviors ====*/
	bool Contains(float& x, float& y);
	void Reveal();
	void ToggleFlag();
	void ToggleMine();
	void Reset();
	void RevealAdjacentTiles();
	void ClearAdjacentTiles();

	/*==== Mutators ====*/
	void SetMine(bool hasMine);
	void SetPosition(float x, float y);
	void AddAdjacentTile(Tile* neighbor);

	/*==== Accessors ====*/
	const sf::Sprite& GetTileSprite() const;
	const sf::Sprite& GetMineSprite() const;
	const sf::Sprite& GetFlagSprite() const;
	const sf::Sprite& GetNumSprite() const;
	bool IsRevealed() const;
	bool MineRevealed() const;
	bool HasMine() const;
	bool HasFlag() const;
	int GetNumAdjacentMines() const;
};