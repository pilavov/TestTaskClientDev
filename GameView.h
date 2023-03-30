//
// Created by kpilavov on 30.03.23.
//

#ifndef TEST_TASK_CLIENT_DEV_GAMEVIEW_H
#define TEST_TASK_CLIENT_DEV_GAMEVIEW_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameModel.h"


class GameView
{
public:
    void render(sf::RenderWindow& window,
                GameModel& model,
                sf::Text& titleText,
                sf::Text& playText,
                sf::Text& difficultyText,
                sf::Text& scoreText,
                sf::Text& gameOverText,
                sf::Text& instructionsText,
                sf::Text& chosenDifficulty);
};



#endif //TEST_TASK_CLIENT_DEV_GAMEVIEW_H
