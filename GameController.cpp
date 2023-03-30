//
// Created by kpilavov on 30.03.23.
//

#include <iostream>
#include "GameController.h"

GameController::GameController(sf::RenderWindow& window)
        : window(window)
{
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Error loading font\n";
    }

    titleText.setFont(font);
    titleText.setString("Ping Pong");
    titleText.setCharacterSize(100);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(SCREEN_WIDTH / 2 - titleText.getLocalBounds().width / 2, 50);

    playText.setFont(font);
    playText.setString("Press Enter to Play");
    playText.setCharacterSize(50);
    playText.setFillColor(sf::Color::White);
    playText.setPosition(SCREEN_WIDTH / 2 - playText.getLocalBounds().width / 2, SCREEN_HEIGHT / 2 - playText.getLocalBounds().height / 2);

    difficultyText.setFont(font);
    difficultyText.setString("Press 1 for Easy, 2 for Medium, 3 for Hard");
    difficultyText.setCharacterSize(50);
    difficultyText.setFillColor(sf::Color::White);
    difficultyText.setPosition(SCREEN_WIDTH / 2 - difficultyText.getLocalBounds().width / 2, SCREEN_HEIGHT / 2 + playText.getLocalBounds().height);

    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(SCREEN_WIDTH / 2 - scoreText.getLocalBounds().width / 2, 50);

    choosenDifficulty.setFont(font);
    choosenDifficulty.setString("Chosen Difficulty : Hard ");
    choosenDifficulty.setCharacterSize(50);
    choosenDifficulty.setFillColor(sf::Color::White);
    choosenDifficulty.setPosition(SCREEN_WIDTH / 2 - choosenDifficulty.getLocalBounds().width / 2, SCREEN_HEIGHT / 2 + difficultyText.getLocalBounds().height+100);

    gameOverText.setFont(font);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(100);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(SCREEN_WIDTH / 2 - gameOverText.getLocalBounds().width / 2, 50);

    instructionsText.setFont(font);
    instructionsText.setString("Press Esc to Quit");
    instructionsText.setCharacterSize(50);
    instructionsText.setFillColor(sf::Color::White);
    instructionsText.setPosition(SCREEN_WIDTH / 2 - instructionsText.getLocalBounds().width / 2, SCREEN_HEIGHT - instructionsText.getLocalBounds().height - 50);
}

void GameController::handleInput(GameModel& model, sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
        }
    }
}

void GameController::update(GameModel& model)
{
    switch (model.gameState)
    {
        case GameState::Menu:
            updateMenu(model);
            break;
        case GameState::Playing:
            updatePlaying(model);
            break;
        case GameState::GameOver:
            updateGameOver(model);
            break;
    }
}

void GameController::render(GameModel& model, GameView& view, sf::RenderWindow& window)
{
    view.render(window, model, titleText, playText, difficultyText, scoreText, gameOverText, instructionsText, choosenDifficulty);
}

void GameController::updateMenu(GameModel& model)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        model.gameState = GameState::Playing;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        model.difficulty = Difficulty::Easy;
        choosenDifficulty.setString("Chosen Difficulty : Easy ");
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        model.difficulty = Difficulty::Medium;
        choosenDifficulty.setString("Chosen Difficulty : Medium ");
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
    {
        model.difficulty = Difficulty::Hard;
        choosenDifficulty.setString("Chosen Difficulty : Hard ");
    }
}

void GameController::updatePlaying(GameModel& model)
{
    updatePaddles(model);
    updateBall(model);
    updateScore(model);

    if (model.score1 >= 11 || model.score2 >= 11)
    {
        model.gameState = GameState::GameOver;
    }

}

void GameController::updateGameOver(GameModel& model)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        model.reset();
    }
}


void GameController::updatePaddles(GameModel& model)
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && model.paddle1->getPosition().y > 0)
    {
        model.paddle1->move(0, -PADDLE_SPEED );
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && model.paddle1->getPosition().y + model.paddle1->getShape().getSize().y < SCREEN_HEIGHT)
    {
        model.paddle1->move(0, PADDLE_SPEED );
    }

    float difficulty_coef = 1;
    // Update bot paddle movement
    float ballY = model.ball->getPosition().y + BALL_RADIUS;
    float paddleY = model.paddle2->getPosition().y + PADDLE_HEIGHT / 2;
    if (model.difficulty != Difficulty::Easy) {
        difficulty_coef = 0.1;
    }
    if (model.difficulty != Difficulty::Medium) {
        difficulty_coef = 0.2;
    }
    if (model.difficulty != Difficulty::Hard) {
        difficulty_coef = 0.35;
    }
    if (model.ballVelocity.x > 0)
    {
        if (paddleY < ballY)
        {
            model.paddle2->move(0, PADDLE_SPEED/difficulty_coef);
        }
        else
        {
            model.paddle2->move(0, -PADDLE_SPEED/difficulty_coef);
        }
    }
    else
    {
        model.paddle2Velocity.y = 0;
    }
}

void GameController::updateBall(GameModel& model)
{

    model.ball->move(model.ballVelocity.x , model.ballVelocity.y );

    // Check collision with top and bottom walls
    if (model.ball->getPosition().y < 0 || model.ball->getPosition().y + model.ball->getShape().getRadius() * 2 > SCREEN_HEIGHT)
    {
        model.ballVelocity.y *= -1;
    }

    // Check collision with paddles
    if (model.ball->getGlobalBounds().intersects(model.paddle1->getGlobalBounds()) || model.ball->getGlobalBounds().intersects(model.paddle2->getGlobalBounds()))
    {
        model.ballVelocity.x *= -1.1f;
        model.ballVelocity.y *= 1.1f;
    }

    // Check if ball has gone out of bounds
    if (model.ball->getPosition().x < 0)
    {
        model.score2++;
        updateScore(model);
        model.reset();
    }
    else if (model.ball->getPosition().x + model.ball->getShape().getRadius() * 2 > SCREEN_WIDTH)
    {
        model.score1++;
        updateScore(model);
        model.reset();
    }

}


void GameController::updateScore(GameModel& model)
{
    scoreText.setString(std::to_string(model.score1) + " - " + std::to_string(model.score2));
    scoreText.setPosition(SCREEN_WIDTH / 2 - scoreText.getLocalBounds().width / 2, 50);
}

