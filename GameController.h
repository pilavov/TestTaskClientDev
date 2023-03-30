//
// Created by kpilavov on 30.03.23.
//

#ifndef TEST_TASK_CLIENT_DEV_GAMECONTROLLER_H
#define TEST_TASK_CLIENT_DEV_GAMECONTROLLER_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "GameModel.h"
#include "GameView.h"


class GameController
{
public:
    GameController(sf::RenderWindow& window);

    void handleInput(GameModel& model, sf::RenderWindow& window);
    void update(GameModel& model);
    void render(GameModel& model, GameView& view, sf::RenderWindow& window);

private:
    sf::Text titleText;
    sf::Text playText;
    sf::Text difficultyText;
    sf::Text scoreText;
    sf::Text gameOverText;
    sf::Text instructionsText;
    sf::Text choosenDifficulty;

    sf::Font font;

    sf::RenderWindow& window;

    void updateMenu(GameModel& model);
    void updatePlaying(GameModel& model);
    void updateGameOver(GameModel& model);


    void updatePaddles(GameModel& model);
    void updateBall(GameModel& model);
    void updateScore(GameModel& model);
};


#endif //TEST_TASK_CLIENT_DEV_GAMECONTROLLER_H
