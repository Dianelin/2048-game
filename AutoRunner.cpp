//
// Created by diane on 2018/6/29.
//

#include "AutoRunner.h"
#include "Board.h"
#include <algorithm>

using namespace std;

const char dirs[] = {'W', 'A', 'S', 'D'};

char AutoRunner::getCmd(Board theBoard) {
    preBoard = theBoard;
    char bestMoveCmd = dirs[0];
    double bestScore = 0;
    for (char dir : dirs) {
        Board child = theBoard;
        child.move(dir);
        double theScore = search(child, 5, -99999999, 99999999, false);
        if (theScore > bestScore) {
            bestScore = theScore;
            bestMoveCmd = dir;
        }
    }
    return bestMoveCmd;
}

double AutoRunner::search(Board currentBoard, int depth, double alpha, double beta, bool player) {
    if(depth == 0 || currentBoard.emptyTileList.empty())
        return getEvalScore(currentBoard);
    if(player) {//玩家
        double bestVal = -99999999;
        for(char dir : dirs){
            Board child = currentBoard;
            child.move(dir);
            bestVal = max(search(child,depth-1,alpha,beta, false),bestVal);
            alpha = max(alpha,bestVal);
            if(beta <= alpha)
                break;

        }
        return bestVal;
    } else{
        double bestValue = 99999999;
        for(int i = 0; i < currentBoard.emptyTileList.size(); i++){
            Board child = currentBoard;
            child.emptyTileList[i]->init();
            bestValue = min(bestValue, search(child,depth-1,alpha,beta,true));
            beta = min(beta,bestValue);
            if(beta <= alpha)
                break;
        }
        return bestValue;
    }

}

double AutoRunner::getEvalScore(Board board) {
    double smoothWeight = 0.3, //平滑性权重系数
            monoWeight = 1.3 , //单调性权重系数
            emptyWeight = 2.7, //空格数权重系数
            maxWeight = 1.8,//最大数权重系数
                    mergeWeight = 0.5;


    return getSmoothness(board) * smoothWeight + getMonotonicScore(board) * monoWeight
           + getEmptyScore(board) * emptyWeight + getMaxScore(board) * maxWeight + getMergeScore(board) * mergeWeight ;
}


int AutoRunner::getSmoothness(Board board) {
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
                    if (farthestTile != nullptr && !farthestTile->isEmpty()&& *farthestTile == *tile) {
                        smoothness += value;
                    }
                }
            }
        }
    }

    return smoothness;
}

double AutoRunner::getMonotonicScore(Board board) {
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

double AutoRunner::getEmptyScore(Board board) {
    board.resetTwoTileLists();
    return board.emptyTileList.size();
}

double AutoRunner::getMaxScore(Board board) {
    return log(board.getScore()) / log(2);
}

double AutoRunner::getMergeScore(Board board) {
    int score = board.getMergeScore() - preBoard.getMergeScore();
    if(score == 0)
        return 0;
    return log(score)/log(2);
}



