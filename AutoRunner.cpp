//
// Created by diane on 2018/6/29.
//

#include "AutoRunner.h"
#include "Board.h"
#include <math.h>


char AutoRunner::getCmd(Board theBoard) {
    this->board = theBoard;
    preBoard = theBoard;
    Board secBoard;
    char cmds[] = {'W', 'A', 'S', 'D'};
    double score = 0;
    char bestMoveCmd = cmds[0];
    for (char cmd: cmds) {
        board.move(cmd);
        secBoard = board;
        double theScore = getEvalScore();
        for (char nextCmd : cmds) {
            board.generateTile();
            board.move(nextCmd);
            theScore = getEvalScore() > theScore ? getEvalScore() : theScore;
            board = secBoard;
        }
        std::cout << cmd  << " " << theScore << std::endl;
        if (theScore > score) {
            bestMoveCmd = cmd;
            score = theScore;
        }
        board = preBoard;
    }
    return bestMoveCmd;
}


double AutoRunner::getEvalScore() {
    double smoothWeight = 0.3, //平滑性权重系数
            monoWeight = 1.3, //单调性权重系数
            emptyWeight = 2.7, //空格数权重系数
            maxWeight = 1.8,//最大数权重系数
                    mergeWeight = 0.5;


    return getSmoothness() * smoothWeight + getMonotonicScore() * monoWeight
           + getEmptyScore() * emptyWeight + getMaxScore() * maxWeight + getMergeScore() * mergeWeight ;
}


int AutoRunner::getSmoothness() {
    int smoothness = 0;
    char dirs[] = {'W', 'A'};
    for (int i = 0; i < Board::boardWidth; i++) {
        for (int j = 0; j < Board::boardWidth; j++) {
            Tile *tile = &board.tiles[i][j];
            if (!tile->isEmpty()) {
                double value = log(board.tiles[i][j].getNum()) / log(2);
                for (char dir : dirs) {
                    Tile *farthestTile = tile;
                    while (board.getBefore(farthestTile, dir) != nullptr &&
                           board.getBefore(farthestTile, dir)->isEmpty()) {
                        farthestTile = board.getBefore(farthestTile, dir);
                    }
                    farthestTile = board.getBefore(farthestTile, dir);
                    if (farthestTile != nullptr && !farthestTile->isEmpty()) {
                        double targetValue = log(farthestTile->getNum()) / log(2);
                        if (*farthestTile == *tile) smoothness += value;
                        //smoothness += abs(value - targetValue);
                    }

                }
            }
        }
    }

    return smoothness;
    //return 0;
}

double AutoRunner::getMonotonicScore() {
    double totals[] = {0, 0, 0, 0};//A D W S
    for (int i = 0; i < Board::boardWidth; i++) {
        for (int j = 1; j < Board::boardWidth; j++) {
            Tile *tile = &board.tiles[i][j];
            if (!tile->isEmpty()) {
                double value = log(tile->getNum()) / log(2);
                Tile *tileBefore = tile;
                while (board.getBefore(tileBefore, 'A') != nullptr &&
                       board.getBefore(tileBefore, 'A')->isEmpty()) {
                    tileBefore = board.getBefore(tileBefore, 'A');
                }
                tileBefore = board.getBefore(tileBefore, 'A');
                if(tileBefore != nullptr && !tileBefore->isEmpty()){
                    double targetValue = log(tileBefore->getNum()) / log(2);
                    if (value > targetValue)
                        totals[0] = value - targetValue;
                    else
                        totals[1] = targetValue - value;
                }

            }
        }

    }

    for (int j = 0; j < Board::boardWidth; j++) {
        for (int i = 1; i < Board::boardWidth; i++) {
            Tile *tile = &board.tiles[i][j];
            if (!tile->isEmpty()) {
                double value = log(tile->getNum()) / log(2);
                Tile *tileBefore = tile;
                while (board.getBefore(tileBefore, 'W') != nullptr &&
                       board.getBefore(tileBefore, 'W')->isEmpty()) {
                    tileBefore = board.getBefore(tileBefore, 'W');
                }
                tileBefore = board.getBefore(tileBefore, 'W');
                if(tileBefore != nullptr && !tileBefore->isEmpty()){
                    double targetValue = log(tileBefore->getNum()) / log(2);
                    if (value > targetValue)
                        totals[0] = value - targetValue;
                    else
                        totals[1] = targetValue - value;
                }
            }
        }

    }

    return (totals[0] > totals[1] ? totals[0] : totals[1]) + (totals[2] > totals[3] ? totals[2] : totals[3]);

}

double AutoRunner::getEmptyScore() {
    board.resetTwoTileLists();
    return board.emptyTileList.size();
}

double AutoRunner::getMaxScore() {
    return log(board.getScore()) / log(2);
}

double AutoRunner::getMergeScore() {
    int score = board.getMergeScore() - preBoard.getMergeScore();
    if(score == 0)
        return 0;
    return log(score)/log(2);
}


