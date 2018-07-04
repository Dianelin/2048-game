//
// Created by diane on 2018/6/29.
//

#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H

#include "Board.h"
class Game{
    Board board;
    Board preBoard;
    int erasePropCount;
    int shufflePropCount;
    const int limitTime;
public:
    Game();
    void run();
    void autoRun();
    void listen();
    void dealCmd(char cmd);
    bool isWin();
    bool isOver();
    void paintGUI();
    void timeCount();
   // void getCmd();

};
#endif //PROJECT_GAME_H
