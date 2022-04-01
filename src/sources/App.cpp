#include <gtkmm-3.0/gtkmm.h>
#include <gtkmm-3.0/gtkmm/applicationwindow.h>
#include <gtkmm-3.0/gtkmm/builder.h>
#include <iostream>
#include <ostream>
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
  Gtk::Button *Feas = nullptr;
  Gtk::Button *Exemp = nullptr;
  Gtk::Button *Opt = nullptr;
  Gtk::Button *Omniopt = nullptr;

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
  pAppWin->set_default_size(800, 500);
  if (pAppWin) {
    // TODO: EVENT HANDLER STUBS HERE
    // Get the GtkBuilder-instantiated Button, and connect a signal handler:
    // buttons for file upload
    refBuilder->get_widget("Attri_FU_But", files.pAttri);
    refBuilder->get_widget("Constraint_FU_But", files.pConst);
    refBuilder->get_widget("Pen_FU_But", files.pPenL);
    refBuilder->get_widget("Poss_FU_But", files.pPossL);
    refBuilder->get_widget("Qual_FU_But", files.pQual);

    // buttons for Manual Entry Append
    refBuilder->get_widget("Attri_Man_But", but.pAttri);
    refBuilder->get_widget("Constraint_Man_But", but.pConst);
    refBuilder->get_widget("Pen_Man_But", but.pPenL);
    refBuilder->get_widget("Poss_Man_But", but.pPossL);
    refBuilder->get_widget("Qual_Man_But", but.pQual);

    // 4 function buttons
    refBuilder->get_widget("Omni_Opt_But", Omniopt);
    refBuilder->get_widget("Opt_But", Opt);
    refBuilder->get_widget("Exemplification_But", Exemp);
    refBuilder->get_widget("Feasability_But", Feas);

    // if getting button was successfull, bind the button to the signal
    // Connections to the File Upload Button Entries
    if (files.pAttri != nullptr) {
      files.pAttri->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    }
    if (files.pConst != nullptr) {
      files.pConst->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    }
    if (files.pPenL != nullptr) {
      files.pPenL->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    }
    if (files.pPossL != nullptr) {
      files.pPossL->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    }
    if (files.pQual != nullptr) {
      files.pQual->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    }
    // Connections to the Manual Button Entries
    if (but.pAttri != nullptr) {
      but.pAttri->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    }
    if (but.pConst != nullptr) {
      but.pConst->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    }
    if (but.pPenL != nullptr) {
      but.pPenL->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    }
    if (but.pPossL != nullptr) {
      but.pPossL->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    }
    if (but.pQual != nullptr) {
      but.pQual->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    }
    // Connections to the 4 functional buttons
    if (Omniopt != nullptr) {
      Omniopt->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    }
    if (Opt != nullptr) {
      Opt->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    }
    if (Exemp != nullptr) {
      Exemp->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    }
    if (but.pPossL != nullptr) {
      Feas->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    }
    if (but.pQual != nullptr) {
      but.pQual->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    }
    app->run(*pAppWin);
  }
  return 0;
}
