#include "alarm.h"

#include <iostream>
#include <unistd.h>
#include <string>

std::string active_alarm = "";

void on_alarm_activated(std::string alarmid)
{
    std::cout << "Alarm " << alarmid  << " activated." << std::endl;
    active_alarm = alarmid;
}

void on_alarm_deactivated(std::string alarmid)
{
    std::cout << "Alarm " << alarmid  << " deactivated." << std::endl;
    active_alarm = "";
}

int main(int argc, char* argv[])
{
    AlarmMgr alarm_mgr;

    alarm_mgr.signal_alarm_activated().connect(sigc::ptr_fun(on_alarm_activated));
    alarm_mgr.signal_alarm_deactivated().connect(sigc::ptr_fun(on_alarm_deactivated));

    while(true) {
        alarm_mgr.check_alarms();
        if(!active_alarm.empty()) {
            std::cout << "ALARM" << std::endl;
            alarm_mgr.deactivate_alarm(active_alarm, true);
        }
        sleep(5);
    }
}
