#include "display/display.h"
#include <gtkmm.h>

int main(int argc, char* argv[])
{

    Glib::OptionContext options("Sunrise Alarm Clock");
    options.set_help_enabled();

    Glib::OptionGroup group("sunrise", "Sunrise");

    bool maximize = false;
    Glib::OptionEntry entry3;
    entry3.set_long_name("maximize");
    entry3.set_short_name('m');
    entry3.set_description("Maximize the window.");
    group.add_entry(entry3, maximize);

    options.set_main_group(group);

    Gtk::Main kit(argc, argv, options);

    Gtk::Window window;
    window.set_title("Sunrise");

    Display disp;
    window.add(disp);
    disp.show();

    if(maximize) window.fullscreen();

    Gtk::Main::run(window);
    return 0;
}
