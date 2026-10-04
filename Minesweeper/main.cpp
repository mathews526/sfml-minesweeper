#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Board.h"
#include "Buttons.h"
#include "Counter.h"
#include "TextureManager.h"
using namespace std;

int main()
{
    Board board;
    Counter counter = Counter(board.GetRemainingMines(), 21, board.GetHeight() - 100);
    vector<Button*> buttons;
    PushBackButtons(buttons, board.GetWidth(), board.GetHeight());

    sf::RenderWindow window(sf::VideoMode(board.GetWidth(), board.GetHeight()), "Minesweeper");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                float x = static_cast<float>(mousePosition.x);
                float y = static_cast<float>(mousePosition.y);
                board.MousePress(x, y);
                
                for (unsigned int i = 0; i < buttons.size(); i++)
                {
                    if (buttons[i]->Contains(x, y))
                        buttons[i]->MousePress(board);
                }
                counter.UpdateSprites(board.GetRemainingMines());
            }
        }

        if (board.IsGameWon())
            buttons[0]->UpdateSprite("face_win");
        else if (board.IsGameLost())
            buttons[0]->UpdateSprite("face_lose");
        else
            buttons[0]->UpdateSprite("face_happy");

        window.clear();

        board.DrawTiles(window);
        for (unsigned int i = 0; i < buttons.size(); i++)
            buttons[i]->DrawButton(window);
        counter.DrawCounter(window);

        window.display();
    }
    
    for (unsigned int i = 0; i < buttons.size(); i++)
        delete buttons[i];

    TextureManager::Clear();
    return 0;
}