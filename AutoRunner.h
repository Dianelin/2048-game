//
// Created by diane on 2018/6/29.
//

#ifndef PROJECT_AUTORUNNER_H
#define PROJECT_AUTORUNNER_H

#include "Board.h"
class AutoRunner{
    Board preBoard;
    double getEvalScore(Board board);
    int getSmoothness(Board board);
    double getEmptyScore(Board board);
    double getMonotonicScore(Board board);
    double getMaxScore(Board board);
    double getMergeScore(Board board);
    double search(Board currentBoard,int depth, double alpha, double beta , bool player);

public:
    char getCmd(Board board);
};
#endif //PROJECT_AUTORUNNER_H
