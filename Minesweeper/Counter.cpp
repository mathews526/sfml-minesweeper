#include "TextureManager.h"
#include "Counter.h"

Counter::Counter(const int& remainingMines, const int& x, const int& y) : _isNegative(false)
{
	for (unsigned int i = 0; i < 3; i++)
	{
		_digitSprites[i].setTexture(TextureManager::GetTexture("digits"));
		_digitSprites[i].setPosition(static_cast<float>(x + i * 21), static_cast<float>(y));
	}
	_digitSprites[3].setTexture(TextureManager::GetTexture("digits"));
	_digitSprites[3].setPosition(static_cast<float>(x - 21), static_cast<float>(y));

	UpdateSprites(remainingMines);
}

void Counter::UpdateSprites(const int& remainingMines)
{
	int num = remainingMines;
	if (num < 0)
	{
		num = -num;
		_isNegative = true;
	}
	else
		_isNegative = false;

	_ones = num % 10;
	_tens = (num / 10) % 10;
	_hundreds = (num / 100) % 10;

	_digitSprites[3].setTextureRect(sf::IntRect(21 * 10, 0, 21, 32));
	_digitSprites[0].setTextureRect(sf::IntRect(21 * _hundreds, 0, 21, 32));
	_digitSprites[1].setTextureRect(sf::IntRect(21 * _tens, 0, 21, 32));
	_digitSprites[2].setTextureRect(sf::IntRect(21 * _ones, 0, 21, 32));
}

void Counter::DrawCounter(sf::RenderWindow& window)
{
	for (unsigned int i = 0; i < 3; i++)
		window.draw(_digitSprites[i]);
	if (_isNegative)
		window.draw(_digitSprites[3]);
}