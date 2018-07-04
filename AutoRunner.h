//
// Created by diane on 2018/6/29.
//

#ifndef PROJECT_AUTORUNNER_H
#define PROJECT_AUTORUNNER_H

#include "Board.h"
class AutoRunner{
    Board board;
    double getEvalScore();
    int getSmoothness();
    double getEmptyScore();
    double getMonotonicScore();
    double getMaxScore();
public:
    AutoRunner(Board board){
        this->board = board;
    };
    char getCmd(Board board);
};
#endif //PROJECT_AUTORUNNER_H
