#ifndef GTKMM_SUNRISE_DISPLAY_H
#define GTKMM_SUNRISE_DISPLAY_H

#include <gtkmm/drawingarea.h>
#include <string>
#include <iostream>
#include "../alarm/alarm_mgr.h"

class Display : public Gtk::DrawingArea
{
    public:
        Display();
        virtual ~Display();

    protected:
        //Override default signal handler:
        bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
        bool on_timeout();
        bool on_key_press_event(GdkEventKey* key_event) override;

        void on_alarm_activated(std::string alarmid);
        void on_alarm_deactivated(std::string alarmid);

    private:
        void draw_rectangle(const Cairo::RefPtr<Cairo::Context>& cr,
                int width, int height);
        void draw_text(const Cairo::RefPtr<Cairo::Context>& cr,
                int rectangle_width, int rectangle_height,
                int xpos, int ypos,
                Glib::ustring text);

        void draw_main_text(const Cairo::RefPtr<Cairo::Context>& cr,
                int rectangle_width, int rectangle_height,
                Glib::ustring text);

        AlarmMgr alarm_mgr;
        std::string active_alarm;
};

#endif // GTKMM_SUNRISE_DISPLAY_H
