//
// Created by diane on 2018/6/29.
//

#ifndef PROJECT_BOARD_H
#define PROJECT_BOARD_H

#include "Tile.h"
#include <vector>
#include <random>

class Board{
    const static int boardWidth = 4;
    Tile tiles[boardWidth][boardWidth];
    std::vector<Tile*> emptyTileList;
    std::vector<Tile*> initedTileList;
    int mergeScore;
    void resetTwoTileLists();
    void resetMerged();
    void moveTile(Tile* tile, char dir);
    Tile* getBefore(Tile*, char dir);

public:
    Board();
    friend class AutoRunner;
    void init();
    void move(char dir);
    void eraseTile();
    void generateTile();
    void shuffleBoard();
    void paint();
    int getScore();
    bool notMovable();
    int getMergeScore(){ return mergeScore;};

};
#endif //PROJECT_BOARD_H
