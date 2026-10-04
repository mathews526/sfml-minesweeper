#include <string>
#include <vector>
#include "Buttons.h"
#include "TextureManager.h"
using namespace std;

/*==== Button Functions ====*/
Button::Button(const string& fileName, int x, int y)
{
	buttonSprite.setTexture(TextureManager::GetTexture(fileName));
	buttonSprite.setPosition(static_cast<float>(x), static_cast<float>(y));
}
Button::~Button()
{

}
bool Button::Contains(float& x, float& y) const
{
	return buttonSprite.getGlobalBounds().contains(x, y);
}
void Button::DrawButton(sf::RenderWindow& window)
{
	window.draw(buttonSprite);
}
void Button::UpdateSprite(const string& fileName)
{
	buttonSprite.setTexture(TextureManager::GetTexture(fileName));
}

/*==== ResetButton Functions ====*/
ResetButton::ResetButton(const string& fileName, int x, int y)
	: Button(fileName, x, y)
{

}
void ResetButton::MousePress(Board& board)
{
	board.ResetBoard("boards/config.cfg");
}

/*==== DebugButton Functions ====*/
DebugButton::DebugButton(const string& fileName, int x, int y)
	: Button(fileName, x, y)
{

}
void DebugButton::MousePress(Board& board)
{
	board.DebugRevealMines();
}

/*==== TestButton Functions ====*/
TestButton::TestButton(const string& fileName, const string& testFileName, int x, int y)
	: Button(fileName, x, y), _testFileName(testFileName)
{

}
void TestButton::MousePress(Board& board)
{
	board.LoadBoardFromFile(_testFileName);
}

/*==== Main.cpp Function Definition ====*/
void PushBackButtons(vector<Button*>& buttons, const int& windowWidth, const int& windowHeight)
{
	int centerWidth = (windowWidth / 2) - 32;
	int buttonHeight = windowHeight - 100;
	buttons.push_back(new ResetButton("face_happy", centerWidth, buttonHeight));
	buttons.push_back(new DebugButton("debug", centerWidth + 128, buttonHeight));
	buttons.push_back(new TestButton("test_1", "testboard1", centerWidth + 192, buttonHeight));
	buttons.push_back(new TestButton("test_2", "testboard2", centerWidth + 256, buttonHeight));
	buttons.push_back(new TestButton("test_3", "testboard3", centerWidth + 320, buttonHeight));
}