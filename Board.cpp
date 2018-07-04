//
// Created by diane on 2018/6/29.
//
#include "Board.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;

unsigned seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());

Board::Board() {
    mergeScore = 0;
    init();

}

void Board::init() {
    for (int i = 0; i < boardWidth; i++) {
        for (int j = 0; j < boardWidth; j++) {
            tiles[i][j].setLocation(i,j);
        }
    }
    resetTwoTileLists();
    generateTile();
    generateTile();
}

void Board::move(char dir) {
    resetMerged();
    switch (dir){
        case 'W':
            for (int j = 0; j < boardWidth; j++) {
                for (int i = 1; i < boardWidth; i++) {
                    if (!tiles[i][j].isEmpty())
                        moveTile(&tiles[i][j],dir);
                }
            }
            break;
        case 'S':
            for (int j = 0; j < boardWidth; j++) {
                for (int i = boardWidth - 1; i >=0 ; i--) {
                    if (!tiles[i][j].isEmpty())
                        moveTile(&tiles[i][j],dir);
                }
            }
            break;
        case 'A':
            for (int i = 0; i < boardWidth; i++) {
                for (int j = 1; j < boardWidth; j++) {
                    if (!tiles[i][j].isEmpty())
                        moveTile(&tiles[i][j],dir);
                }
            }
            break;
        case 'D':
            for (int i = 0; i < boardWidth; i++) {
                for (int j = boardWidth-1; j >=0; j--) {
                    if (!tiles[i][j].isEmpty())
                        moveTile(&tiles[i][j],dir);
                }
            }
            break;
        default:
            cout << "Invalid cmd"<<endl;
    }
    resetTwoTileLists();

}

void Board::eraseTile() {
    shuffle(begin(initedTileList), end(initedTileList), default_random_engine(seed));
    initedTileList[0]->erase();
    resetTwoTileLists();
}

void Board::generateTile() {
    //int location = static_cast<int>(rand() % emptyTileList.size());
    shuffle(emptyTileList.begin(), emptyTileList.end(), default_random_engine(seed));
    emptyTileList[0]->init();
    resetTwoTileLists();
}

void Board::shuffleBoard() {
    shuffle(begin(tiles[0]), end(tiles[boardWidth - 1]), default_random_engine(seed));
    resetTwoTileLists();
}

void Board::paint() {
    for (int i = 0; i < 4; i++) {
        cout << "-----------------------------\n";
        cout << "|";
        for (int j = 0; j < 4; j++) {
            int num = tiles[i][j].getNum();
            if(num == 0)
                cout << setw(6)<<" " <<"|";
            else{
                int lenOfNum = 0;
                int tmpNum = num;
                while (tmpNum / 10 > 0){
                    tmpNum = tmpNum / 10;
                    lenOfNum++;
                }
                int lenOfSpace = (6 - lenOfNum)/2 ;
                for(int m=0; m < lenOfSpace;m++){
                    cout << " ";
                }
                cout <<left<< setw(6-lenOfSpace)<<num <<"|";
            }
        }
        cout << endl;
    }
    cout << "-----------------------------\n";
}

Tile* Board::getBefore(Tile* tile, char dir) {
    int x = tile->getX();
    int y = tile->getY();
    switch (dir) {
        case 'W':
            x--;
            break;
        case 'S':
            x++;
            break;
        case 'A':
            y--;
            break;
        case 'D':
            y++;
            break;
        default:
            x = -1;
            y = -1;
    }
    if(x > -1 && y>-1&& x<boardWidth && y<boardWidth)
        return &tiles[x][y];
    return nullptr;
}

void Board::moveTile(Tile* tile, char dir) {
    Tile* theTile = tile;
    Tile* beforeTile = getBefore(theTile,dir);
    while (beforeTile != nullptr){
        if(beforeTile->isEmpty()){
            *beforeTile = *theTile;
            theTile->erase();
        } else if(*beforeTile == *theTile && !beforeTile->isMerged() && !theTile->isMerged()){
            beforeTile->merge();
            mergeScore += beforeTile->getNum();
            theTile->erase();
        }
        theTile = beforeTile;
        beforeTile = getBefore(theTile,dir);
    }
}

void Board::resetTwoTileLists() {
    emptyTileList.clear();
    initedTileList.clear();
    for (int i = 0; i < boardWidth; i++) {
        for (int j = 0; j < boardWidth; j++) {
            tiles[i][j].isEmpty() ? emptyTileList.push_back(&tiles[i][j]) : initedTileList.push_back(&tiles[i][j]);
        }
    }
}

void Board::resetMerged() {
    for (int i = 0; i < boardWidth; i++) {
        for (int j = 0; j < boardWidth; j++) {
            tiles[i][j].resetMerged();
        }
    }
}

int Board::getScore() {
    int score = 0;
    for (int i = 0; i < boardWidth; i++) {
        for (int j = 0; j < boardWidth; j++) {
            score = tiles[i][j].getNum() > score ? tiles[i][j].getNum() : score;
        }
    }
    return score;
}

bool Board::notMovable() {
    for (int i = 0; i < boardWidth; i++) {
        for (int j = 0; j < boardWidth; j++) {
            Tile* tile = &tiles[i][j];
            if(tile->isEmpty())  return false;
            char dirs[]= {'W','A','S','D'};
            for(char dir : dirs){
                Tile* beforeTile = getBefore(tile,dir);
                if(beforeTile != nullptr && *beforeTile == *tile) return false;
            }
        }
    }
    return true;
}

int Board::getMergeableScore() {
    int mergableScore = 0;
    for (int i = 0; i < boardWidth; i++) {
        for (int j = 0; j < boardWidth; j++) {
            Tile* tile = &tiles[i][j];
            char dirs[]= {'W','A','S','D'};
            for(char dir : dirs){
                Tile* beforeTile = getBefore(tile,dir);
                if(beforeTile != nullptr && *beforeTile == *tile)
                    mergableScore += tile->getNum();
            }
        }
    }
    return mergableScore;
}





