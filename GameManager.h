//
// Created by diane on 2018/6/29.
//

#ifndef PROJECT_GAMEMANAGER_H
#define PROJECT_GAMEMANAGER_H

#include "Game.h"
#include "TimeRecorder.h"
#include <string>
class GameManager{
    TimeRecorder timeRecorder;
    Game game;
    void init();
    void dealGameOver();
public:
    GameManager();
    void listen();

};

#endif //PROJECT_GAMEMANAGER_H
