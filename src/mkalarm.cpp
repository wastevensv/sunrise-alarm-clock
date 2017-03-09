#include <algorithm>
#include <ctime>
#include <climits>
#include <iostream>
#include <string>

#include "arg_parser.hpp"
#include "alarm/alarm.h"

int main(int argc, char* argv[]) {

    ArgParser input(argc, argv);

    struct tm alarm_time;
    if(!strptime(argv[1], "%H:%M", &alarm_time)) return -1;

    int dow;
    std::string dow_str = input.getOption("-d");
    if(!dow_str.empty()) {
        dow = std::stoi(dow_str);
    } else {
        dow = -1;
    }

    std::string alarmid = input.getOption("-n");
    if(!alarmid.empty()) alarmid="alarm";

    std::string start_date_str = input.getOption("-b");
    struct tm start_date;
    if(!start_date_str.empty()) {
        if(!strptime(start_date_str.c_str(), "%Y-%m-%d", &start_date)) return -1;
    } else {
        time_t rawtime;
        time(&rawtime);
        start_date = *localtime(&rawtime);
    }

    std::string stop_date_str = input.getOption("-e");
    struct tm stop_date;
    if(!stop_date_str.empty()) {
        if(!strptime(stop_date_str.c_str(), "%Y-%m-%d", &stop_date)) return -1;
    } else {
        time_t rawtime = INT_MAX;
        stop_date = *localtime(&rawtime);
    }

    std::cout << alarmid << " " << dow << " " << asctime(&alarm_time) << std::endl;
    std::cout << asctime(&start_date);
    std::cout << asctime(&stop_date);
}
