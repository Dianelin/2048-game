//
// Created by diane on 2018/6/29.
//

#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H

#include "Board.h"
class Game{
    Board board;
    int erasePropCount;
    int shufflePropCount;
    const int limitTime;
public:
    Game();
    friend class AutoRunner;
    void run();
    void autoRun();
    void dealCmd(char cmd);
    bool isWin();
    bool isOver();
    void paintGUI();

};
#endif //PROJECT_GAME_H
