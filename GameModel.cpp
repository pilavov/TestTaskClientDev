//
// Created by kpilavov on 30.03.23.
//

#include "GameModel.h"

void GameModel::reset()
{
    paddle1 = paddleFactory.createPaddle(50, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2);
    paddle2 = paddleFactory.createPaddle(SCREEN_WIDTH - 50 - PADDLE_WIDTH, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2);
    ball = ballFactory.createBall(SCREEN_WIDTH / 2 - BALL_RADIUS, SCREEN_HEIGHT / 2 - BALL_RADIUS);

    paddle1Velocity = sf::Vector2f(0, 0);
    paddle2Velocity = sf::Vector2f(0, 0);
    ballVelocity = sf::Vector2f(BALL_SPEED, distribution(generator));


}
