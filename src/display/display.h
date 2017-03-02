#ifndef GTKMM_SUNRISE_DISPLAY_H
#define GTKMM_SUNRISE_DISPLAY_H

#include <gtkmm/drawingarea.h>

class Display : public Gtk::DrawingArea
{
    public:
        Display();
        virtual ~Display();

    protected:
        //Override default signal handler:
        bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
        bool on_timeout();

    private:
        void draw_rectangle(const Cairo::RefPtr<Cairo::Context>& cr,
                int width, int height);
        void draw_text(const Cairo::RefPtr<Cairo::Context>& cr,
                int rectangle_width, int rectangle_height,
                Glib::ustring text);
};

#endif // GTKMM_SUNRISE_DISPLAY_H
