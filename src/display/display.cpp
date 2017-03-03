#include <ctime>
#include <cmath>
#include <cairomm/context.h>
#include <glibmm/main.h>
#include "display.h"

Display::Display()
{
    Glib::signal_timeout().connect( sigc::mem_fun(*this, &Display::on_timeout), 1000 );
}

Display::~Display()
{
}

bool Display::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    const int rectangle_width = width;
    const int rectangle_height = height;

    // Draw a black rectangle
    cr->set_source_rgb(0.0, 0.0, 0.0);
    draw_rectangle(cr, rectangle_width, rectangle_height);

    // Get the time.
    time_t rawtime;
    time(&rawtime);
    struct tm * timeinfo = localtime (&rawtime);

    char timestr[80];
    strftime(timestr,80,"%a %b %d\n%r",timeinfo);

    // Draw the time on the display
    cr->set_source_rgb(1.0, 1.0, 1.0);
    draw_text(cr, rectangle_width, rectangle_height, timestr);
    return true;
}

bool Display::on_timeout()
{
    // force our program to redraw the entire clock.
    auto win = get_window();
    if (win)
    {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(),
                get_allocation().get_height());
        win->invalidate_rect(r, false);
    }
    return true;
}


void Display::draw_rectangle(const Cairo::RefPtr<Cairo::Context>& cr,
        int width, int height)
{
    cr->rectangle(0, 0, width, height);
    cr->fill();
}

void Display::draw_text(const Cairo::RefPtr<Cairo::Context>& cr,
        int rectangle_width, int rectangle_height,
        Glib::ustring text)
{
    // http://developer.gnome.org/pangomm/unstable/classPango_1_1FontDescription.html
    Pango::FontDescription font;

    //  font.set_family("Monospace");
    font.set_weight(Pango::WEIGHT_BOLD);

    // http://developer.gnome.org/pangomm/unstable/classPango_1_1Layout.html
    auto layout = create_pango_layout(text);

    layout->set_font_description(font);

    int text_width;
    int text_height;

    //get the text dimensions (it updates the variables -- by reference)
    layout->get_pixel_size(text_width, text_height);

    // Position the text in the middle
    cr->move_to((rectangle_width-text_width)/2, (rectangle_height-text_height)/2);

    layout->show_in_cairo_context(cr);
}
