#pragma once
#include <SFML/Graphics.hpp>

class Counter
{
	sf::Sprite _digitSprites[4];
	int _ones;
	int _tens;
	int _hundreds;
	bool _isNegative;
public:
	Counter(const int& remainingMines, const int& x, const int& y);
	void UpdateSprites(const int& remainingMines);
	void DrawCounter(sf::RenderWindow& window);
};