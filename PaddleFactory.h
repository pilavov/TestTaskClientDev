//
// Created by kpilavov on 29.03.23.
//

#ifndef _C___CLIENT_DEVELOPER_PADDLEFACTORY_H
#define _C___CLIENT_DEVELOPER_PADDLEFACTORY_H


#include <memory>
#include "Paddle.h"

class PaddleFactory
{
public:
    std::unique_ptr<Paddle> createPaddle(float x, float y);
};

#endif //_C___CLIENT_DEVELOPER_PADDLEFACTORY_H
