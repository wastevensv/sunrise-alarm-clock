#ifndef GTKMM_SUNRISE_ALARM_H
#define GTKMM_SUNRISE_ALARM_H

#include <string>
#include <ctime>
#include <sigc++/sigc++.h>
#include <sqlite/connection.hpp>

class AlarmMgr
{
    public:
        AlarmMgr();
        AlarmMgr(std::string alarmdb_name);
        virtual ~AlarmMgr();

        // Check alarm list, emit signal if alarm active
        void check_alarms();

        // Set an alarm manually.
        void set_alarm(std::string alarmid, tm* alarm_time, tm* start_date, tm* stop_date);

        // Emit signal to deactivate an alarm
        void deactivate_alarm(std::string alarmid, bool snooze);

        // Emit signal to deactivate all alarms
        void deactivate_alarm();

        // Shared alarm signal type
        typedef sigc::signal<void, std::string> type_signal_alarm;

        // Alarm Activate signal accessor
        type_signal_alarm signal_alarm_activated();
        // Alarm Deactivate signal accessor
        type_signal_alarm signal_alarm_deactivated();

    protected:
        type_signal_alarm m_signal_alarm_activated;
        type_signal_alarm m_signal_alarm_deactivated;
        sqlite::connection alarmdb;
        enum class col_names{id=0, series_name, dow, hr, min, start_date, stop_date, last_run};
};

#endif
