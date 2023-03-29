//
// Created by kpilavov on 29.03.23.
//

#include <iostream>
#include "Game.h"

Game::Game()
        : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Ping Pong", sf::Style::Fullscreen),
          generator(std::time(nullptr)),
          distribution(-2, 2),
          difficulty(Difficulty::Easy),
          gameState(GameState::Menu),
          score1(0),
          score2(0)
{
    window.setFramerateLimit(60);

    // Load the font
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // Set up the text objects
    titleText.setFont(font);
    titleText.setCharacterSize(100);
    titleText.setPosition(SCREEN_WIDTH / 2 - 300, 50);
    titleText.setFillColor(sf::Color::White);
    titleText.setString("Ping Pong");

    playText.setFont(font);
    playText.setCharacterSize(50);
    playText.setPosition(SCREEN_WIDTH / 2 - 100, 300);
    playText.setFillColor(sf::Color::White);
    playText.setString("Play");

    difficultyText.setFont(font);
    difficultyText.setCharacterSize(50);
    difficultyText.setPosition(SCREEN_WIDTH / 2 - 100, 400);
    difficultyText.setFillColor(sf::Color::White);
    difficultyText.setString("Difficulty: Easy (just stays in one place) ");

    instructionsText.setFont(font);
    instructionsText.setCharacterSize(30);
    instructionsText.setPosition(50, SCREEN_HEIGHT - 100);
    instructionsText.setFillColor(sf::Color::White);
    instructionsText.setString("Press left and right key arrows to change difficulty\nPress W and S to move the paddle\nPress Enter to start");

    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setPosition(SCREEN_WIDTH / 2 - 200, 50);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setString("USER: 0           BOT: 0");

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(100);
    gameOverText.setPosition(SCREEN_WIDTH / 2 - 400, 200);
    gameOverText.setFillColor(sf::Color::White);

    reset();
}


void Game::run()
{
    while (window.isOpen())
    {
        handleInput();
        update();
        render();
    }
}

void Game::handleInput()
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

void Game::update()
{

    switch (gameState)
    {
        case GameState::Menu:
            updateMenu();
            break;
        case GameState::Playing:
            updatePlaying();
            break;
        case GameState::GameOver:
            updateGameOver();
            break;
    }
}

void Game::render()
{
    window.clear(sf::Color::Black);

    switch (gameState)
    {
        case GameState::Menu:
            renderMenu();
            break;
        case GameState::Playing:
            renderPlaying();
            break;
        case GameState::GameOver:
            renderGameOver();
            break;
    }

    window.display();
}


void Game::reset()
{
    paddle1 = paddleFactory.createPaddle(50, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2);
    paddle2 = paddleFactory.createPaddle(SCREEN_WIDTH - 50 - PADDLE_WIDTH, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2);
    ball = ballFactory.createBall(SCREEN_WIDTH / 2 - BALL_RADIUS, SCREEN_HEIGHT / 2 - BALL_RADIUS);

    ballVelocity = sf::Vector2f(BALL_SPEED, distribution(generator));

    score1 = 0;
    score2 = 0;
}


void Game::showMenu()
{
    gameState = GameState::Menu;
}

void Game::updateMenu()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        gameState = GameState::Playing;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (difficulty == Difficulty::Easy)
        {
            difficulty = Difficulty::Medium;
            difficultyText.setString("Difficulty: Medium");
        }
        else if (difficulty == Difficulty::Medium)
        {
            difficulty = Difficulty::Hard;
            difficultyText.setString("Difficulty: Hard");
        }
        else
        {
            difficulty = Difficulty::Easy;
            difficultyText.setString("Difficulty: Easy");
        }

        sf::sleep(sf::milliseconds(200));
    }
}

void Game::updatePlaying()
{
    // Handle paddle 1 movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        paddle1Velocity.y = -PADDLE_SPEED;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        paddle1Velocity.y = PADDLE_SPEED;
    }
    else
    {
        paddle1Velocity.y = 0;
    }

    // Update paddle and ball positions
    paddle1->move(paddle1Velocity.x, paddle1Velocity.y);
    paddle2->move(paddle2Velocity.x, paddle2Velocity.y);
    ball->move(ballVelocity.x, ballVelocity.y);

    // Handle collisions with the screen edges
    if (paddle1->getPosition().y < 0)
    {
        paddle1->setPosition(paddle1->getPosition().x, 0);
    }
    if (paddle1->getPosition().y > SCREEN_HEIGHT - PADDLE_HEIGHT)
    {
        paddle1->setPosition(paddle1->getPosition().x, SCREEN_HEIGHT - PADDLE_HEIGHT);
    }
    if (ball->getPosition().y < 0 || ball->getPosition().y > SCREEN_HEIGHT - BALL_RADIUS * 2)
    {
        ballVelocity.y = -ballVelocity.y;
    }

    // Handle collisions with the paddles
    if (ball->getGlobalBounds().intersects(paddle1->getGlobalBounds()))
    {
        ballVelocity.x = std::abs(ballVelocity.x);
    }
    if (ball->getGlobalBounds().intersects(paddle2->getGlobalBounds()))
    {
        ballVelocity.x = -std::abs(ballVelocity.x);
    }

    // Update bot paddle movement
    if (difficulty != Difficulty::Easy)
    {
        float ballY = ball->getPosition().y + BALL_RADIUS;
        float paddleY = paddle2->getPosition().y + PADDLE_HEIGHT / 2;

        if (ballVelocity.x > 0)
        {
            if (difficulty == Difficulty::Medium)
            {
                if (paddleY < ballY)
                {
                    paddle2Velocity.y = PADDLE_SPEED;
                }
                else
                {
                    paddle2Velocity.y = -PADDLE_SPEED;
                }
            }
            else if (difficulty == Difficulty::Hard)
            {
                float ballX = ball->getPosition().x + BALL_RADIUS;
                float paddleX = paddle2->getPosition().x + PADDLE_WIDTH;
                float time = (paddleX - ballX) / ballVelocity.x;
                float predictedY = ballY + ballVelocity.y * time;
                if (predictedY < 0 || predictedY > SCREEN_HEIGHT - PADDLE_HEIGHT)
                {
                    return;
                }
                if (paddleY < predictedY)
                {
                    paddle2Velocity.y = PADDLE_SPEED;
                }
                else if (paddleY > predictedY)
                {
                    paddle2Velocity.y = -PADDLE_SPEED;
                }
            }
        }
        else
        {
            paddle2Velocity.y = 0;
        }
    }

    // Handle scoring
    if (ball->getPosition().x < 0)
    {
        score2++;
        ball->setPosition(SCREEN_WIDTH / 2 - BALL_RADIUS, SCREEN_HEIGHT / 2 - BALL_RADIUS);
        ballVelocity.x = BALL_SPEED;
        ballVelocity.y = distribution(generator);
    }

    if (ball->getPosition().x > SCREEN_WIDTH - BALL_RADIUS * 2)
    {
        score1++;
        ball->setPosition(SCREEN_WIDTH / 2 - BALL_RADIUS, SCREEN_HEIGHT / 2 - BALL_RADIUS);
        ballVelocity.x = -BALL_SPEED;
        ballVelocity.y = distribution(generator);
    }

    scoreText.setString("USER: " + std::to_string(score1) + "           BOT: " + std::to_string(score2));

    if (score1 >= 10 || score2 >= 10)
    {
        gameOverText.setString("Player " + std::to_string(score1 >= 10 ? 1 : 2) + " wins!");
        gameState = GameState::GameOver;
    }
}

void Game::updateGameOver()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        reset();
        showMenu();
    }
}

void Game::renderMenu()
{
    window.draw(titleText);
    window.draw(playText);
    window.draw(difficultyText);
    window.draw(instructionsText);
}

void Game::renderPlaying()
{
    window.draw(paddle1->getShape());
    window.draw(paddle2->getShape());
    window.draw(ball->getShape());
    window.draw(scoreText);
}

void Game::renderGameOver()
{
    window.draw(gameOverText);
    window.draw(scoreText);
}

Game &Game::getInstance() {
    static Game instance;
    return instance;
}
