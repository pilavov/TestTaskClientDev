//
// Created by kpilavov on 29.03.23.
//

#ifndef _C___CLIENT_DEVELOPER_PADDLE_H
#define _C___CLIENT_DEVELOPER_PADDLE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


class Paddle
{
public:
    Paddle(float x, float y);

    void move(float dx, float dy);

    const sf::RectangleShape& getShape() const;

    void setPosition ( float x , float y);

    const sf::Vector2f& getPosition () const;

    sf::FloatRect getGlobalBounds () const;


private:
    sf::RectangleShape shape;
};



#endif //_C___CLIENT_DEVELOPER_PADDLE_H
