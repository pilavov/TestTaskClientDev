cmake_minimum_required(VERSION 3.24)
project(Test_task_client_dev)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

add_executable(Test_task_client_dev main.cpp config.h Paddle.cpp Paddle.h Ball.cpp Ball.h PaddleFactory.cpp PaddleFactory.h BallFactory.cpp BallFactory.h Game.cpp Game.h GameModel.cpp GameModel.h GameView.cpp GameView.h GameController.cpp GameController.h)

target_link_libraries(Test_task_client_dev sfml-system sfml-window sfml-graphics sfml-audio)