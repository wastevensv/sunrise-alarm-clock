#include "alarm_mgr.h"
#include <iostream>
#include <sqlite/execute.hpp>
#include <sqlite/query.hpp>

AlarmMgr::AlarmMgr() : AlarmMgr::AlarmMgr("alarm.db") {}
AlarmMgr::AlarmMgr(std::string alarmdb_name) : alarmdb(alarmdb_name)
{
    try
    {
        sqlite::execute(alarmdb, "CREATE TABLE alarms"
                "("
                " id INTEGER PRIMARY KEY,"
                " series_name TEXT,"
                " dow INT,"
                " hr INT,"
                " min INT,"
                " start_date DATE,"
                " stop_date DATE"
                ");", true);
    }
    catch(std::exception const & e)
    {
        std::cerr << e.what() << std::endl;
    }
}
AlarmMgr::~AlarmMgr() {}

void AlarmMgr::check_alarms()
{
    // Get the time.
    time_t rawtime;
    time(&rawtime);
    struct tm* timeinfo = localtime (&rawtime);

    m_signal_alarm_activated.emit("test");
}

void AlarmMgr::set_alarm(std::string alarmid, tm* alarm_time, tm* start_date, tm* stop_date) {
    std::cout << "Alarm " << alarmid << " set for " << asctime(alarm_time) << std::endl;
    time_t start_time = mktime(start_date);
    time_t stop_time = mktime(stop_date);
    sqlite::execute ins(alarmdb, "INSERT INTO alarms VALUES(?, ?, ?, ?, ?, ?, ?);");
    ins % sqlite::nil % alarmid % alarm_time->tm_wday % alarm_time->tm_hour % alarm_time->tm_min % start_time % stop_time;
    ins();
}

void AlarmMgr::deactivate_alarm(std::string alarmid, bool snooze)
{
    m_signal_alarm_deactivated.emit(alarmid);
    if(snooze)
    {
        time_t rawtime;
        time(&rawtime);

        struct tm start_date = *localtime(&rawtime);

        struct tm alarm_time = *localtime(&rawtime);
        alarm_time.tm_min = alarm_time.tm_min + 3;

        struct tm end_date = *localtime(&rawtime);
        end_date.tm_mday = end_date.tm_mday + 1;

        set_alarm("snooze", &alarm_time, &start_date, &end_date);
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
