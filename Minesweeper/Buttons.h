#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Board.h"
using std::string;
using std::vector;

/*==== Base Class ====*/
struct Button
{
	/*==== Constructor / Destructor ====*/
	Button(const string& fileName, int x, int y);
	virtual ~Button();

	/*==== Behaviors ====*/
	virtual void MousePress(Board& board) = 0;
	bool Contains(float& x, float& y) const;
	void DrawButton(sf::RenderWindow& window);
	void UpdateSprite(const string& fileName);
protected:
	sf::Sprite buttonSprite;
};

/*==== Derived Buttons ====*/
struct ResetButton : public Button
{
	ResetButton(const string& fileName, int x, int y);
	void MousePress(Board& board);
};
struct DebugButton : public Button
{
	DebugButton(const string& fileName, int x, int y);
	void MousePress(Board& board);
};
struct TestButton : public Button
{
	TestButton(const string& fileName, const string& testFileName, int x, int y);
	void MousePress(Board& board);
private:
	string _testFileName;
};

/*==== Main.cpp Function Prototype ====*/
void PushBackButtons(vector<Button*>& buttons, const int& windowWidth, const int& windowHeight);