//
// Created by diane on 2018/6/29.
//

#ifndef PROJECT_TILE_H
#define PROJECT_TILE_H

#include <iostream>

class Tile {
    int num;
    int x;
    int y;
    bool merged;
public:
    Tile() : x(0), y(0), num(0), merged(false) {};

    Tile &operator=(const Tile &tile) {
        this->num = tile.num;
    }

    bool operator==(const Tile &tile) {
        return (this->num == tile.num);
    }

    void init() {
        int n = rand() % 10;
        if (n > 7)
            num = 4;
        else
            num = 2;
    }

    bool isEmpty() { return (num == 0); }

    void merge() {
        num *= 2;
        merged = true;
    }

    void erase() {
        num = 0;
        merged = false;
    }

    void setLocation(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int getX() { return x; };

    int getY() { return y; };

    int getNum() { return num; }

    bool isMerged() { return merged; };

    bool resetMerged() { merged = false; }
};

#endif //PROJECT_TILE_H
