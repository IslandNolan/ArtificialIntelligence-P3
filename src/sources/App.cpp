#include <gtkmm-3.0/gtkmm.h>
#include <gtkmm-3.0/gtkmm/applicationwindow.h>
#include <gtkmm-3.0/gtkmm/builder.h>
#include <iostream>
#include <p3/p3.h>

Gtk::ApplicationWindow *pAppWin = nullptr;

struct FileUp {
  Gtk::Button *pAttri = nullptr;
  Gtk::Button *pConst = nullptr;
  Gtk::Button *pPenL = nullptr;
  Gtk::Button *pPossL = nullptr;
  Gtk::Button *pQual = nullptr;
};
typedef struct FileUp FUP;
struct ManBut {
  Gtk::Button *pAttri = nullptr;
  Gtk::Button *pConst = nullptr;
  Gtk::Button *pPenL = nullptr;
  Gtk::Button *pPossL = nullptr;
  Gtk::Button *pQual = nullptr;
};

typedef struct ManBut MB;

static void on_button_clicked() { std::cout << "BUTTON CLICKED" << std::endl; }

int wininit(int argc, char **argv) {
  // Initalize a new application type
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.IntelliApp");
  // Initalize a Builder that will generate the UI later
  auto refBuilder = Gtk::Builder::create();
  FUP files;
  MB but;
  try {
    // Tell the builder what UI to use
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
  // tell refBuilder what the parent window is
  refBuilder->get_widget("Intelligent Application", pAppWin);
  if (pAppWin) {
    // TODO: EVENT HANDLER STUBS HERE
    // Get the GtkBuilder-instantiated Button, and connect a signal handler:
    refBuilder->get_widget("Attri_FU_But", files.pAttri);
    // if getting button was successfull, bind the button to the signal
    // TODO:  Other buttons only trigger after first button is pressed
    if (files.pAttri) {
      files.pAttri->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    }
    refBuilder->get_widget("Constraint_FU_But", files.pConst);
    if (files.pConst) {
      files.pAttri->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    }
    refBuilder->get_widget("Pen_FU_But", files.pPenL);
    if (files.pPenL) {
      files.pAttri->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    }
    refBuilder->get_widget("Poss_FU_But", files.pPossL);
    if (files.pPossL) {
      files.pAttri->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    }
    refBuilder->get_widget("Qual_FU_But", files.pQual);
    if (files.pQual) {
      files.pAttri->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    }

    app->run(*pAppWin);
  }
  return 0;
}
