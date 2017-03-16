#include <algorithm>
#include <ctime>
#include <climits>
#include <iostream>
#include <string>
#include <iomanip>

#include "arg_parser.hpp"
#include "alarm/alarm.h"

enum WeekDay {ALL=-1, SUN, MON, TUE, WED, THU, FRI, SAT};

const std::string wdtostr(WeekDay wd) {
    switch(wd) {
        case ALL:
            return "Everyday";
        case SUN:
            return "Sunday";
        case MON:
            return "Monday";
        case TUE:
            return "Tuesday";
        case WED:
            return "Wednesday";
        case THU:
            return "Thursday";
        case FRI:
            return "Friday";
        case SAT:
            return "Saturday";
    }
}

WeekDay strtowd(std::string str) {
    if(str == "Sunday" || str == "Sun") {
        return SUN;
    } else if(str == "Monday" || str == "Mon") {
        return MON;
    } else if(str == "Tuesday" || str == "Tue") {
        return TUE;
    } else if(str == "Wednesday" || str == "Wed") {
        return WED;
    } else if(str == "Thursday" || str == "Thu") {
        return THU;
    } else if(str == "Friday" || str == "Fri") {
        return FRI;
    } else if(str == "Saturday" || str == "Sat") {
        return SAT;
    } else {
        return ALL;
    }
}

int main(int argc, char* argv[]) {

    ArgParser input(argc, argv);

    struct tm alarm_time;
    if(!strptime(argv[1], "%H:%M", &alarm_time) || input.optionExists("-h")) {
        std::cerr << "Usage: " << argv[0] << " HH:MM [-d W] [-n id] [-b YYYY-MM-DD] [-e YYYY-MM-DD] [-db filename]" << std::endl;
        std::cerr << "HH:MM         | Alarm time" << std::endl;
        std::cerr << "-d W          | Alarm weekday (Sunday or Sun)" << std::endl;
        std::cerr << "-n id         | Alarm id" << std::endl;
        std::cerr << "-b YYYY-MM-DD | Alarm start date" << std::endl;
        std::cerr << "-e YYYY-MM-DD | Alarm end date" << std::endl;
        return -2;
    }

    std::string dow_str = input.getOption("-d");
    WeekDay dow;
    if(!dow_str.empty()) {
        dow = strtowd(dow_str);
    } else {
        dow = WeekDay::ALL;
    }

    std::string alarmid = input.getOption("-n");
    if(alarmid.empty()) alarmid="alarm";

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
        time_t endtime = INT_MAX;
        stop_date = *localtime(&endtime);
    }

    std::string db_filename = input.getOption("-db");
    if(db_filename.empty()) db_filename = "alarm.db";
    AlarmMgr alarm_mgr(db_filename);
    alarm_mgr.set_alarm(alarmid, (int)dow, &alarm_time, &start_date, &stop_date);

    std::cout << alarmid << ' ' << wdtostr(dow) << ' ';

    std::cout << std::setw(2) << std::setfill('0');
    std::cout << alarm_time.tm_hour;

    std::cout << ':';

    std::cout << std::setw(2) << std::setfill('0');
    std::cout << alarm_time.tm_min << std::endl;


    std::cout << "Start Date: ";
    std::cout << std::setw(4) << std::setfill('0') << 1900 + start_date.tm_year;
    std::cout << "-";
    std::cout << std::setw(2) << std::setfill('0') << start_date.tm_mon;
    std::cout << "-";
    std::cout << std::setw(2) << std::setfill('0') << start_date.tm_mday;
    std::cout << std::endl;

    std::cout << "Stop Date:  ";
    std::cout << std::setw(4) << std::setfill('0') << 1900 + stop_date.tm_year;
    std::cout << "-";
    std::cout << std::setw(2) << std::setfill('0') << stop_date.tm_mon;
    std::cout << "-";
    std::cout << std::setw(2) << std::setfill('0') << stop_date.tm_mday;
    std::cout << std::endl;
}
