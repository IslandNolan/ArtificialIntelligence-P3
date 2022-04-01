#include <gtkmm-3.0/gtkmm.h>
#include <gtkmm-3.0/gtkmm/applicationwindow.h>
#include <gtkmm-3.0/gtkmm/builder.h>
#include <iostream>

Gtk::ApplicationWindow *pAppWin = nullptr;

static void on_button_clicked() { std::cout << "BUTTON CLICKED" << std::endl; }

int wininit(int argc, char **argv) {
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.IntelliApp");
  auto refBuilder = Gtk::Builder::create();
  try {
    refBuilder->add_from_file("Project3.glade");
  } catch (const Glib::FileError &ex) {
    std::cerr << "FileError: " << ex.what() << std::endl;
    return 1;
  } catch (const Glib::MarkupError &ex) {
    std::cerr << "MarkupError: " << ex.what() << std::endl;
    return 1;
  } catch (const Gtk::BuilderError &ex) {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
    return 1;
  }

  refBuilder->get_widget("Intelligent Application", pAppWin);
  if (pAppWin) {
    // Get the GtkBuilder-instantiated Button, and connect a signal handler:
    Gtk::Button *pButton = nullptr;
    refBuilder->get_widget("Attri_FU_But", pButton);
    if (pButton) {
      pButton->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    }

    app->run(*pAppWin);
  }
  return 0;
}
