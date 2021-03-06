//
// Created by diane on 2018/6/30.
//

#ifndef PROJECT_TIMER_H
#define PROJECT_TIMER_H

#include <chrono>
#include <ctime>
#include <vector>
#include <string>
using namespace std::chrono;
class TimeRecorder{
    std::vector<long> timeRecordsList;
    clock_t start;
public:
    TimeRecorder();
    void read();
    std::string endRecord();
    void display();
    void startRecord();
    std::string getStringByDuration(long duration);
};
#endif //PROJECT_TIMER_H
