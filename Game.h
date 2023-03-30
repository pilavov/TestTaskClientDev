//
// Created by kpilavov on 29.03.23.
//

#ifndef _C___CLIENT_DEVELOPER_GAME_H
#define _C___CLIENT_DEVELOPER_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <random>
#include "BallFactory.h"
#include "Ball.h"
#include "PaddleFactory.h"
#include "Paddle.h"
#include "config.h"
#include "GameController.h"
#include "GameView.h"

class Game {
public:
    static Game& getInstance();

    void run();

private:
    Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    GameModel model;
    GameView view;
    GameController controller;

    sf::RenderWindow window;
    sf::Font font;
    sf::Text titleText;
    sf::Text playText;
    sf::Text difficultyText;
    sf::Text scoreText;
    sf::Text gameOverText;
    sf::Text instructionsText;


};


#endif //_C___CLIENT_DEVELOPER_GAME_H
