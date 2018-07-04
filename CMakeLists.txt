cmake_minimum_required(VERSION 3.10)
project(project)

set(CMAKE_CXX_STANDARD 11)

add_executable(project main.cpp GameManager.cpp GameManager.h Game.cpp Game.h Board.cpp Board.h Tile.cpp Tile.h AutoRunner.cpp AutoRunner.h TimeRecorder.cpp TimeRecorder.h)