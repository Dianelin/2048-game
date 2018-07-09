//
// Created by diane on 2018/6/30.
//

#include "TimeRecorder.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
using namespace std;

TimeRecorder::TimeRecorder() {
    read();
    start = clock();
}

void TimeRecorder::read() {
    ifstream in("recorder");
    if(!in)
        return;
    while(!in.eof()){
        long record;
        in >> record;
        timeRecordsList.push_back(record);
    }
}

void TimeRecorder::startRecord() {
    start = clock();
}

string TimeRecorder::endRecord() {
    clock_t end = clock();
    long duration =  (long)(end - start) / CLOCKS_PER_SEC;
    timeRecordsList.push_back(duration);
    ofstream out("recorder");
    out << duration;
    out.close();
    return getStringByDuration(duration);
}

void TimeRecorder::display() {
    std::sort(timeRecordsList.begin(),timeRecordsList.end());
    for(int i = 0; i < timeRecordsList.size();i++){
        cout<<std::setw(3)<< i << "  " << getStringByDuration(timeRecordsList[i])<<endl;
    }
}

std::string TimeRecorder::getStringByDuration(long duration) {
    int hour = duration / 3600;
    int min =  duration % 3600 / 60;
    int sec = duration % 3600 % 60;
    string timeStr = std::to_string(hour) + ":" + std::to_string(min) +":"+ std::to_string(sec);
    return timeStr;
}



