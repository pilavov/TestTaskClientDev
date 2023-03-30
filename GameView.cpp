//
// Created by kpilavov on 30.03.23.
//

#include "GameView.h"


void GameView::render(sf::RenderWindow& window, GameModel& model, sf::Text& titleText, sf::Text& playText, sf::Text& difficultyText, sf::Text& scoreText, sf::Text& gameOverText, sf::Text& instructionsText, sf::Text& chosenDifficulty)
{
    window.clear(sf::Color::Black);

    switch (model.gameState)
    {
        case GameState::Menu:
            window.draw(titleText);
            window.draw(playText);
            window.draw(difficultyText);
            window.draw(instructionsText);
            window.draw(chosenDifficulty);
            break;
        case GameState::Playing:
            window.draw(model.paddle1->getShape());
            window.draw(model.paddle2->getShape());
            window.draw(model.ball->getShape());
            window.draw(scoreText);
            break;
        case GameState::GameOver:
            window.draw(gameOverText);
            window.draw(scoreText);
            break;
    }

    window.display();
}