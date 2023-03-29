//
// Created by kpilavov on 29.03.23.
//

#include "Ball.h"
#include "config.h"

Ball::Ball(float x, float y) {
    shape.setRadius(BALL_RADIUS);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Red);
}

void Ball::move(float dx, float dy) {
    shape.move(dx, dy);
}

const sf::CircleShape &Ball::getShape() const {
    return shape;
}

void Ball::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

const sf::Vector2f &Ball::getPosition() const {
    return shape.getPosition();
}

sf::FloatRect Ball::getGlobalBounds() const {
    return shape.getGlobalBounds();
}
