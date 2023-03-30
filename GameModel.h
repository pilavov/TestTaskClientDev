//
// Created by kpilavov on 30.03.23.
//

#ifndef TEST_TASK_CLIENT_DEV_GAMEMODEL_H
#define TEST_TASK_CLIENT_DEV_GAMEMODEL_H

#include <memory>
#include <random>
#include "config.h"
#include "Paddle.h"
#include "Ball.h"
#include "PaddleFactory.h"
#include "BallFactory.h"

class GameModel {
public:
    void reset();
    GameModel() : generator(std::time(nullptr)), distribution(-2, 2) {}

    Difficulty difficulty;
    GameState gameState;
    int score1 = 0;
    int score2 = 0;

    std::unique_ptr<Paddle> paddle1;
    std::unique_ptr<Paddle> paddle2;
    std::unique_ptr<Ball> ball;

    // Paddle and Ball factories
    PaddleFactory paddleFactory;
    BallFactory ballFactory;

    sf::Vector2f paddle1Velocity;
    sf::Vector2f paddle2Velocity;
    sf::Vector2f ballVelocity;

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;
};

#endif //TEST_TASK_CLIENT_DEV_GAMEMODEL_H
