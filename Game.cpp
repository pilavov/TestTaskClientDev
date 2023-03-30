#include <iostream>
#include "Game.h"

Game::Game()
        : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Ping Pong", sf::Style::Fullscreen),
          controller(window)
{
    window.setFramerateLimit(60);

    // Load the font
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    model.reset();
}

void Game::run()
{
    while (window.isOpen())
    {
        controller.handleInput(model, window);
        controller.update(model);
        controller.render(model, view, window);
    }
}

Game &Game::getInstance() {
    static Game instance;
    return instance;
}
