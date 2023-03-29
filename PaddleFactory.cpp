//
// Created by kpilavov on 29.03.23.
//

#include "PaddleFactory.h"

std::unique_ptr <Paddle> PaddleFactory::createPaddle(float x, float y) {
    return std::make_unique<Paddle>(x, y);
}
