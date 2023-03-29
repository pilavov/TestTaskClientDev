//
// Created by kpilavov on 29.03.23.
//

#ifndef _C___CLIENT_DEVELOPER_BALLFACTORY_H
#define _C___CLIENT_DEVELOPER_BALLFACTORY_H


#include <memory>
#include "Ball.h"

class BallFactory
{
public:
    std::unique_ptr<Ball> createBall(float x, float y);
};


#endif //_C___CLIENT_DEVELOPER_BALLFACTORY_H
