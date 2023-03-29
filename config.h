//
// Created by kpilavov on 29.03.23.
//

#ifndef _C___CLIENT_DEVELOPER_CONFIG_H
#define _C___CLIENT_DEVELOPER_CONFIG_H


const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int PADDLE_WIDTH = 20;
const int PADDLE_HEIGHT = 100;
const int BALL_RADIUS = 10;

const float PADDLE_SPEED = 5.f;
inline float BALL_SPEED = 15.f;

enum class Difficulty
{
    Easy,
    Medium,
    Hard
};

enum class GameState
{
    Menu,
    Playing,
    GameOver
};

#endif //_C___CLIENT_DEVELOPER_CONFIG_H
