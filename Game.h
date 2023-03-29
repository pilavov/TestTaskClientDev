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

class Game
{
public:
    static Game& getInstance();

    void run();

private:
    Game();
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    void handleInput();
    void update();
    void render();
    void reset();
    void showMenu();
    void updateMenu();
    void updatePlaying();
    void updateGameOver();
    void renderMenu();
    void renderPlaying();
    void renderGameOver();

    sf::RenderWindow window;
    sf::Font font;
    sf::Text titleText;
    sf::Text playText;
    sf::Text difficultyText;
    sf::Text scoreText;
    sf::Text gameOverText;
    sf::Text instructionsText;

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;

    Difficulty difficulty;
    GameState gameState;
    int score1;
    int score2;

    // Paddle and Ball instances
    std::unique_ptr<Paddle> paddle1;
    std::unique_ptr<Paddle> paddle2;
    std::unique_ptr<Ball> ball;

    // Paddle and Ball factories
    PaddleFactory paddleFactory;
    BallFactory ballFactory;

    sf::Vector2f paddle1Velocity;
    sf::Vector2f paddle2Velocity;
    sf::Vector2f ballVelocity;
};


#endif //_C___CLIENT_DEVELOPER_GAME_H
