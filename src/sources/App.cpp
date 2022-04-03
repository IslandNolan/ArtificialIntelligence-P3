#include "p3/p3.h"
#include <glibmm/refptr.h>
#include <gtkmm-3.0/gtkmm/applicationwindow.h>
#include <gtkmm-3.0/gtkmm/builder.h>
//#include <gtkmm-3.0/gtkmm/dialog.h>
#include <gtkmm-3.0/gtkmm/enums.h>
#include <gtkmm-3.0/gtkmm/scrolledwindow.h>
#include <gtkmm-3.0/gtkmm/textbuffer.h>
#include <gtkmm-3.0/gtkmm/textview.h>
#include <iostream>

Gtk::ApplicationWindow *pAppWin = nullptr;

// Tidy the different kinds of buttons
struct FileUp {
  Gtk::Button *pAttri = nullptr;
  Gtk::Button *pConst = nullptr;
  Gtk::Button *pPenL = nullptr;
  Gtk::Button *pPossL = nullptr;
  Gtk::Button *pQual = nullptr;
};
typedef struct FileUp FUP;

struct FuncBut {
  Gtk::Button *Feas = nullptr;
  Gtk::Button *Exemp = nullptr;
  Gtk::Button *Opt = nullptr;
  Gtk::Button *Omniopt = nullptr;
};

typedef struct FuncBut FB;

// TODO: turn Attriview into a tree view
//  The different view to display the text buffers
Gtk::TextView *AttriView = nullptr, *ConstView = nullptr, *PrefView = nullptr,
              *ResultView = nullptr;
/*
Gtk::ScrolledWindow *AttriScroll = nullptr, *ConstScroll = nullptr,
                    *PrefScroll = nullptr, *ResScroll = nullptr;
*/
void onFeasClick() {
  std::cout << "Feas Clicked" << std::endl;
  bufferFeasability();
}
void onExemClick() {
  std::cout << "Example click" << std::endl;
  bufferExemplification();
}
void onOptiClick() {
  std::cout << "Optimal Clicked" << std::endl;
  bufferOptimization();
}
void onOmniClick() {
  std::cout << "Omni Optimal Clicked" << std::endl;
  bufferOmniOptimization();
}

// Pass argc and argv from Main
int wininit(int argc, char **argv) {
  std::cout << "CREATING APPLICATION" << std::endl;
  // Initalize a new application type
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.IntelliApp");
  // Initalize a Builder that will generate the UI later
  auto refBuilder = Gtk::Builder::create();
  FUP files;
  FB fun;
  initBuffers(); // initalize all the buffers
  // BufferTestInit(); // fill the buffers with test text
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

    // 4 function buttons
    refBuilder->get_widget("Omni_Opt_But", fun.Omniopt);
    refBuilder->get_widget("Opt_But", fun.Opt);
    refBuilder->get_widget("Exemplification_But", fun.Exemp);
    refBuilder->get_widget("Feasability_But", fun.Feas);

    // Connections to the File Upload Button Entries
    files.pAttri->signal_clicked().connect(sigc::ptr_fun(onAttributeUpload));
    files.pConst->signal_clicked().connect(sigc::ptr_fun(onConstraintsUpload));
    files.pPenL->signal_clicked().connect(sigc::ptr_fun(onPenaltyFileUpload));
    files.pPossL->signal_clicked().connect(
        sigc::ptr_fun(onPossibilisticUpload));
    files.pQual->signal_clicked().connect(sigc::ptr_fun(onQualitativeUpload));
    // TODO: have manual buttons append text to their buffers

    // Connections to the 4 functional buttons
    fun.Omniopt->signal_clicked().connect(sigc::ptr_fun(onOmniClick));
    fun.Opt->signal_clicked().connect(sigc::ptr_fun(onOptiClick));
    fun.Exemp->signal_clicked().connect(sigc::ptr_fun(onExemClick));
    fun.Feas->signal_clicked().connect(sigc::ptr_fun(onFeasClick));

    // TextViews
    refBuilder->get_widget("Attri_Prev", AttriView);
    refBuilder->get_widget("Const_Prev", ConstView);
    refBuilder->get_widget("Pref_Prev", PrefView);
    refBuilder->get_widget("Res_View", ResultView);

    AttriView->set_buffer(getAttriBuff());
    ConstView->set_buffer(getConstBuff());
    PrefView->set_buffer(getPrefBuff());
    ResultView->set_buffer(getResultBuff());
  }

  // Run the application
  app->run(*pAppWin);
  return 0;
}
