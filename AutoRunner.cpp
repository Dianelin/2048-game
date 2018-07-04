//
// Created by diane on 2018/6/29.
//

#include "AutoRunner.h"
#include "Board.h"
#include <math.h>


char AutoRunner::getCmd(Board theBoard) {
    this->board = theBoard;
    Board preBoard = board;
    char cmds[]= {'W','A','S','D'};
    double score = 0;
    char bestMoveCmd = cmds[0];
    for(char cmd: cmds){
        board.move(cmd);
        double theScore = getEvalScore();
        std::cout << cmd << " " << theScore << std::endl;
        if(theScore > score){
            bestMoveCmd = cmd;
            score = theScore;
        }
        board = preBoard;
    }
    return bestMoveCmd;
}

double AutoRunner::getEvalScore() {
    double smoothWeight = 0.5, //平滑性权重系数
            monoWeight = 1.3, //单调性权重系数
            emptyWeight = 2.7, //空格数权重系数
            maxWeight = 1; //最大数权重系数
    return getSmoothness()*smoothWeight + getMonotonicScore()*monoWeight
            +getEmptyScore()*emptyWeight + getMaxScore() * maxWeight;
}

int AutoRunner::getSmoothness() {
    int smoothness = 0;
    char dirs[] ={'W','A'};
    for (int i = 0; i < Board::boardWidth; i++) {
        for (int j = 0; j < Board::boardWidth; j++) {
            Tile* tile = &board.tiles[i][j];
           if(!tile->isEmpty()){
               double value = log(board.tiles[i][j].getNum())/log(2);
               for(char dir : dirs){
                   Tile* farthestTile = tile;
                   while(board.getBefore(farthestTile,dir)!=nullptr && board.getBefore(farthestTile,dir)->isEmpty()){
                       farthestTile = board.getBefore(farthestTile,dir);
                   }
                   farthestTile = board.getBefore(farthestTile,dir);
                   if(farthestTile!= nullptr && !farthestTile->isEmpty()){
                       double targetValue = log(farthestTile->getNum())/log(2);
                       if(*farthestTile == *tile) smoothness += value;
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
    int totals[]={0,0,0,0};
    for(int x=0; x< Board::boardWidth;x++){
        int current = 0;
        int next = current + 1;
//        while (next < Board::boardWidth){
//
//        }
    }
    return 0;
}

double AutoRunner::getEmptyScore() {
    board.resetTwoTileLists();
    return board.emptyTileList.size();
}

double AutoRunner::getMaxScore() {
    return log(board.getScore())/log(2);
}


