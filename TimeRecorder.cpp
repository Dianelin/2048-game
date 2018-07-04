//
// Created by diane on 2018/6/30.
//

#include "TimeRecorder.h"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

void TimeRecorder::save() {
    ofstream out("recorder.txt");
    for(long timeRecord : timeRecordsList){
        out << timeRecord << " ";
    }
    out.close();
}

void TimeRecorder::read() {
    ifstream in("recorder.txt");
    if(!in)
        return;
    while(!in.eof()){
        long record;
        in >> record;
        timeRecordsList.push_back(record);
    }
}

void TimeRecorder::endRecord() {
    clock_t end = clock();
    long duration =  (long)(end - start) / CLOCKS_PER_SEC;
    timeRecordsList.push_back(duration);

}

void TimeRecorder::display() {
    std::sort(timeRecordsList.begin(),timeRecordsList.end());
    for(long timeRecord : timeRecordsList){
        cout<< getStringByDuration(timeRecord)<<endl;
    }
}

void TimeRecorder::startRecord() {
    start = clock();
}

std::string TimeRecorder::getUsedTime() {
    clock_t current = clock();
    long duration =  (long)(current- start) / CLOCKS_PER_SEC;
    return getStringByDuration(duration);
}

std::string TimeRecorder::getStringByDuration(long duration) {
    int hour = duration / 3600;
    int min =  duration % 3600 / 60;
    int sec = duration % 3600 % 60;
    string timeStr = std::to_string(hour) + ":" + std::to_string(min) +":"+ std::to_string(sec);
    return timeStr;
}


