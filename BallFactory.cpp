//
// Created by kpilavov on 29.03.23.
//

#include "BallFactory.h"

std::unique_ptr <Ball> BallFactory::createBall(float x, float y)  {
    return std::make_unique<Ball>(x, y);
}
