#include "alarm_mgr.h"
#include <iostream>

AlarmMgr::AlarmMgr()
{
}

AlarmMgr::~AlarmMgr()
{
}

void AlarmMgr::check_alarms()
{
    // Get the time.
    time_t rawtime;
    time(&rawtime);
    struct tm* timeinfo = localtime (&rawtime);

    // TODO: Change to real alarm check rather than every 5 minutes.
    if (timeinfo->tm_min % 2 == 0)
    {
        m_signal_alarm_activated.emit("test");
    }
}

void AlarmMgr::set_alarm(std::string alarmid, tm* alarm_time) {
    std::cout << "Alarm " << alarmid << " set for " << asctime(alarm_time) << std::endl;
    // TODO: Actually set alarm.
}

void AlarmMgr::deactivate_alarm(std::string alarmid, bool snooze)
{
    m_signal_alarm_deactivated.emit(alarmid);
    if(snooze)
    {
        time_t rawtime;
        time(&rawtime);
        struct tm* timeinfo = localtime(&rawtime);

        timeinfo->tm_min = timeinfo->tm_min + 3;
        set_alarm("snooze", timeinfo);
    }
}

void AlarmMgr::deactivate_alarm()
{
    m_signal_alarm_deactivated.emit("*");
}

AlarmMgr::type_signal_alarm AlarmMgr::signal_alarm_activated()
{
    return m_signal_alarm_activated;
}

AlarmMgr::type_signal_alarm AlarmMgr::signal_alarm_deactivated()
{
    return m_signal_alarm_deactivated;
}
