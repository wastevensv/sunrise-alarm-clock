#include "display/display.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create(argc, argv, "me.wasv.sunrise");

    Gtk::Window window;
    window.set_title("Sunrise");

    Display disp;
    window.add(disp);
    disp.show();

    return app->run(window);
}
