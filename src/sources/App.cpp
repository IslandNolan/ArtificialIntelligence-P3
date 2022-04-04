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

Gtk::TextView *AttriView = nullptr, *ConstView = nullptr, *PrefView = nullptr,
              *ResultView = nullptr, *StatusView = nullptr;

void onFeasClick() {

  std::cout << "Feas Clicked" << std::endl;
  if (!getLoadedAttri()) {
    BufferFlush(getStatusBuff());
    BufferInsert(getStatusBuff(), "Missing Attributes File.. ");
    return;
  } else if (!getSelectedPref()) {
    BufferFlush(getStatusBuff());
    BufferInsert(getStatusBuff(), "Missing Preferences File.. ");
    return;
  } else {
    BufferFlush(getStatusBuff());
    BufferInsert(getStatusBuff(), "Generated Feasibility");
    bufferFeasability();
  }
}
void onExemClick() {
  std::cout << "Exemplification Button Clicked.. " << std::endl;
  if (!getLoadedAttri()) {
    BufferFlush(getStatusBuff());
    BufferInsert(getStatusBuff(), "Missing Attributes File.. ");
    return;
  } else if (!getSelectedPref()) {
    BufferFlush(getStatusBuff());
    BufferInsert(getStatusBuff(), "Missing Preferences File.. ");
    return;
  } else {
    BufferFlush(getStatusBuff());
    BufferInsert(getStatusBuff(), "Generated Exemplification");
    bufferExemplification();
    return;
  }
}
void onOptiClick() {
  std::cout << "Optimal Clicked" << std::endl;
  if (!getLoadedAttri()) {
    BufferFlush(getStatusBuff());
    BufferInsert(getStatusBuff(), "Missing Attributes File.. ");
    return;
  } else if (!getSelectedPref()) {
    BufferFlush(getStatusBuff());
    BufferInsert(getStatusBuff(), "Missing Preferences File.. ");
    return;
  } else {
    BufferFlush(getStatusBuff());
    BufferInsert(getStatusBuff(), "Generated Optimal");
    bufferOptimization();
  }
}
void onOmniClick() {

  std::cout << "Omni-Optimal Clicked" << std::endl;

  if (!getLoadedAttri()) {
    BufferFlush(getStatusBuff());
    BufferInsert(getStatusBuff(), "Missing Attributes File.. ");
    return;
  } else if (!getSelectedPref()) {
    BufferFlush(getStatusBuff());
    BufferInsert(getStatusBuff(), "Missing Preferences File.. ");
    return;
  } else {
    BufferFlush(getStatusBuff());
    BufferInsert(getStatusBuff(), "Generated Omni-Optimal");
    bufferOmniOptimization();
  }
}

// Pass argc and argv from Main
int wininit(int argc, char **argv) {
  std::cout << "CREATING APPLICATION" << std::endl;
  // Initalize a new application type
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.IntelliApp");
  // Initalize a Builder that will generate the UI later
  auto refBuilder = Gtk::Builder::create_from_resource(
      "/org/gtkmm/intelliapp/Project3.glade");
  FUP files;     // Struct contains all the file upload buttons
  FB fun;        // Struct contains all the function buttons
  initBuffers(); // initalize all the buffers
  // BufferTestInit(); // fill the buffers with test text
  // tell refBuilder what the parent window is
  refBuilder->get_widget("Intelligent Application", pAppWin);
  if (pAppWin) {

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
    refBuilder->get_widget("StatView", StatusView);

    AttriView->set_buffer(getAttriBuff());
    ConstView->set_buffer(getConstBuff());
    PrefView->set_buffer(getPrefBuff());
    ResultView->set_buffer(getResultBuff());
    StatusView->set_buffer(getStatusBuff());
  }

  // Run the application
  app->run(*pAppWin);
  return 0;
}
