//
// Created by kpilavov on 29.03.23.
//

#include "Paddle.h"
#include "config.h"

Paddle::Paddle(float x, float y) {
    shape.setSize(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);
}

const sf::RectangleShape &Paddle::getShape() const {
    return shape;
}

const sf::Vector2f &Paddle::getPosition() const {
    return shape.getPosition();
}

void Paddle::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

sf::FloatRect Paddle::getGlobalBounds() const {
    return shape.getGlobalBounds();
}

void Paddle::move(float dx, float dy) {
    shape.move(dx, dy);
}
