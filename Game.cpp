//
// Created by diane on 2018/6/29.
//
#include "Game.h"
#include "AutoRunner.h"
#include <iostream>
#include <string>

#include <chrono>
#include <thread>

using namespace std;

const string cmdMessage  = "Please enter command:  W -- UP; S -- DOWN; A -- LEFT ; D -- RIGHT; Z -- shuffleBoard; X -- random erase; E -- exit;";
char cmd = '0';

void getCmd() {
    cin >> cmd;
    cmd = (char)toupper(cmd);
}

Game::Game():erasePropCount(3),shufflePropCount(3),limitTime(10) {
}

void Game::run() {
    cout << "New Game start!"<<endl;
    board = Board();
    paintGUI();
    cout << cmdMessage << endl;
    cmd = ' 0';
    while (cmd != 'E'){
        cmd = '0';
        thread listenCmdThread(getCmd);
        for(int i = 0 ; i < limitTime;i++){
            if(cmd != '0'){
                listenCmdThread.join();
                if(cmd == 'E')
                    return;
                dealCmd(cmd);
                paintGUI();
                if(isWin() || isOver())
                    return;
                cout<< cmdMessage<< "\n"<< ">> ";
                break;
            } else{
                this_thread::sleep_for(std::chrono::seconds(1));
            }
            if(i == limitTime -1){
                cout << "Time limited! Randomly generated a new Tile!"<<endl;
                board.generateTile();
                paintGUI();
                cout<< cmdMessage<< "\n"<< ">> ";
                cmd = '0';
                i = 0;
            }
        }
    }
    cout << "Successfully exited this game."<<endl;
}
void Game::autoRun() {
    cout << "New Game auto running!"<<endl;
    board = Board();
    AutoRunner autoRunner;
    board.paint();
    while (!isWin() && !isOver()){
        char bestMoveCmd = autoRunner.getCmd(board);
        cout << ">> "<< bestMoveCmd << endl;
        dealCmd(bestMoveCmd);
        paintGUI();
        if(isOver()&& shufflePropCount > 0){
            dealCmd('Z');
            paintGUI();
        }
        if(isOver() && erasePropCount > 0){
            dealCmd('X');
            paintGUI();
        }
    }

}

bool Game::isWin() {
    return (board.getScore() == 2048);
}

bool Game::isOver() {
    return board.notMovable();
}

void Game::paintGUI() {
    cout<< "Score : " << board.getMergeScore() << "; Shuffle prop: "<< shufflePropCount << "; Erase prop: "<< erasePropCount << endl;
    board.paint();
}

void Game::dealCmd(char cmd) {
    switch(cmd){
        case 'Z':
            if(shufflePropCount > 0){
                board.shuffleBoard();
                shufflePropCount--;
            } else{
                cout << "You've used up all shuffle props!"<<endl;
            }
            break;
        case 'X':
            if(erasePropCount > 0){
                board.eraseTile();
                erasePropCount--;
            } else{
                cout << "You've used up all erase props!"<<endl;
            }
            break;
        case 'W':
        case 'S':
        case 'A':
        case 'D':
            board.move(cmd);
            if(isWin()|| isOver()){
                return;
            }
            board.generateTile();
            break;
        default:
            cout << "Invalid command!"<<endl;
    }
}







