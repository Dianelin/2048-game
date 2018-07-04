//
// Created by diane on 2018/6/29.
//

#include <iostream>
#include <string>
#include "GameManager.h"
#include "AutoRunner.h"

using namespace std;

const string remainderString =   "Please enter Command:\n N --- New Game ; E --- Exit ; V --- View Ranking; C --- Auto run game;";
GameManager GameManager::gameManager = GameManager();
GameManager::GameManager() {
    init();
}
void GameManager::init() {
    cout<< "Welcome to 2048!\n"<< remainderString <<endl;
}
GameManager GameManager::getInstance() {
    return gameManager;
}

void GameManager::listen() {
    char cmd;
    cin >> cmd;
    cmd = (char)toupper(cmd);
    while (cmd != 'E'){
        switch (cmd){
            case 'N':
                timeRecorder.startRecord();
                game.run();
                if(game.isWin()){
                    timeRecorder.endRecord();
                    timeRecorder.display();
                }
                if(game.isOver()){

                }
                break;
            case 'C':
                timeRecorder.startRecord();
                game.autoRun();
                break;
            case 'V':
                timeRecorder.display();
                break;
            default:
                cout<< "Invalid Command!" << endl;
        }
        cout <<"------------------------------------------------\n" << remainderString << endl;
        cin >> cmd;
        cmd = (char)toupper(cmd);
    }
    timeRecorder.save();
    cout << "Successfully Exited!" << endl;
}



