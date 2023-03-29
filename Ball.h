//
// Created by kpilavov on 29.03.23.
//

#ifndef _C___CLIENT_DEVELOPER_BALL_H
#define _C___CLIENT_DEVELOPER_BALL_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Ball
{
public:
    Ball(float x, float y);

    void move(float dx, float dy);

    const sf::CircleShape& getShape() const;

    void setPosition ( float x , float y);

    const sf::Vector2f& getPosition () const;

    sf::FloatRect getGlobalBounds () const;

private:
    sf::CircleShape shape;
};


#endif //_C___CLIENT_DEVELOPER_BALL_H
