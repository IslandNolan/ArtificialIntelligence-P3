#include "glibmm/refptr.h"
#include "gtkmm/dialog.h"
#include "gtkmm/enums.h"
#include "gtkmm/filechooser.h"
#include "gtkmm/filechooserdialog.h"
#include <gtkmm-3.0/gtkmm.h>
#include <gtkmm-3.0/gtkmm/applicationwindow.h>
#include <gtkmm-3.0/gtkmm/builder.h>
#include <gtkmm-3.0/gtkmm/scrolledwindow.h>
#include <gtkmm-3.0/gtkmm/textbuffer.h>
#include <gtkmm-3.0/gtkmm/textview.h>
#include <iostream>
#include <ostream>
#include <p3/p3.h>

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
struct ManBut {
  Gtk::Button *pAttri = nullptr;
  Gtk::Button *pConst = nullptr;
  Gtk::Button *pPenL = nullptr;
  Gtk::Button *pPossL = nullptr;
  Gtk::Button *pQual = nullptr;
};

typedef struct ManBut MB;

struct FuncBut {
  Gtk::Button *Feas = nullptr;
  Gtk::Button *Exemp = nullptr;
  Gtk::Button *Opt = nullptr;
  Gtk::Button *Omniopt = nullptr;
};

typedef struct FuncBut FB;

// Buffers for each kind of data to display to be sent to a text or tree view
Glib::RefPtr<Gtk::TextBuffer> AttriBuff, ConstBuff, PrefBuff, FeasBuff,
    ExempBuff, OptBuff, OmniOpBuff;
// The different view to display the text buffers
Gtk::TextView *AttriView = nullptr, *ConstView = nullptr, *PrefView = nullptr;

Gtk::ScrolledWindow *AttriScroll = nullptr, *ConstScroll = nullptr,
                    *PrefScroll = nullptr, *ResScroll = nullptr;
bool init = false;
void initBuffers() {
  std::cout << "INITALIZING BUFFERS" << std::endl;
  AttriBuff = Gtk::TextBuffer::create();
  ConstBuff = Gtk::TextBuffer::create();
  PrefBuff = Gtk::TextBuffer::create();
  FeasBuff = Gtk::TextBuffer::create();
  ExempBuff = Gtk::TextBuffer::create();
  OptBuff = Gtk::TextBuffer::create();
  OmniOpBuff = Gtk::TextBuffer::create();
  init = true;
}

void BufferTestInit() {
  if (!init) {
    std::cout << "BUFFERS NOT INITALIZED" << std::endl;
    return;
  } else {
    AttriBuff->set_text("AttriBuff working");
    ConstBuff->set_text("ConstBuff working");
    PrefBuff->set_text("PrefBuff working");
    FeasBuff->set_text("FeasBuff working");
    ExempBuff->set_text("ExempBuff working");
    OptBuff->set_text("OptBuff working");
    OmniOpBuff->set_text("OmniOpBuff working");
  }
}
void initButtons(Gtk::Builder *refBuilder, FUP files, MB but, FB fun) {
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
  refBuilder->get_widget("Omni_Opt_But", fun.Omniopt);
  refBuilder->get_widget("Opt_But", fun.Opt);
  refBuilder->get_widget("Exemplification_But", fun.Exemp);
  refBuilder->get_widget("Feasability_But", fun.Feas);
}

void on_button_file_clicked() {
  Gtk::FileChooserDialog dialog("please choose a file",
                                Gtk::FILE_CHOOSER_ACTION_OPEN);
  // dialog.set_transient_for(*this);
  // Add response buttons to the dialog:
  dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
  dialog.add_button("_Open", Gtk::RESPONSE_OK);

  // Add filters, so that only certain file types can be selected:
  // text only
  auto filter_text = Gtk::FileFilter::create();
  filter_text->set_name("Text files");
  filter_text->add_mime_type("text/plain");
  dialog.add_filter(filter_text);
  // any file type
  auto filter_any = Gtk::FileFilter::create();
  filter_any->set_name("Any files");
  filter_any->add_pattern("*");
  dialog.add_filter(filter_any);

  int result = dialog.run();
  // Handle the response:
  switch (result) {
  case (Gtk::RESPONSE_OK): {
    std::cout << "Open clicked." << std::endl;

    // Notice that this is a std::string, not a Glib::ustring.
    std::string filename = dialog.get_filename();
    std::cout << "File selected: " << filename << std::endl;
    break;
  }
  case (Gtk::RESPONSE_CANCEL): {
    std::cout << "Cancel clicked." << std::endl;
    break;
  }
  default: {
    std::cout << "Unexpected button clicked." << std::endl;
    break;
  }
  }
}

static void on_button_clicked() { std::cout << "BUTTON CLICKED" << std::endl; }

// Pass argc and argv from Main
int wininit(int argc, char **argv) {
  std::cout << "CREATING APPLICATION" << std::endl;
  // Initalize a new application type
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.IntelliApp");
  // Initalize a Builder that will generate the UI later
  auto refBuilder = Gtk::Builder::create();
  FUP files;
  MB but;
  FB fun;
  // AttriBuff = Gtk::TextBuffer::create();
  // AttriBuff->set_text("AttriBuff working");
  initBuffers();    // initalize all the buffers
  BufferTestInit(); // fill the buffers with test text
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
    refBuilder->get_widget("Omni_Opt_But", fun.Omniopt);
    refBuilder->get_widget("Opt_But", fun.Opt);
    refBuilder->get_widget("Exemplification_But", fun.Exemp);
    refBuilder->get_widget("Feasability_But", fun.Feas);

    // TODO: get file upload buttons to prompt for file upload
    // Connections to the File Upload Button Entries
    files.pAttri->signal_clicked().connect(
        sigc::ptr_fun(on_button_file_clicked));
    files.pConst->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    files.pPenL->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    files.pPossL->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    files.pQual->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    // TODO: have manual buttons append text to their buffers
    // Connections to the Manual Button Entries
    but.pAttri->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    but.pConst->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    but.pPenL->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    but.pPossL->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    but.pQual->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    // Connections to the 4 functional buttons
    fun.Omniopt->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    fun.Opt->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    fun.Exemp->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    fun.Feas->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));

    // ScrollViews
    refBuilder->get_widget("ScrollWinAttriPrev", AttriScroll);
    refBuilder->get_widget("ScrollWinConstPrev", ConstScroll);
    refBuilder->get_widget("ScrollWinPrefPrev", PrefScroll);
    refBuilder->get_widget("ScrollWinResPrev", ResScroll);
    AttriScroll->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    ConstScroll->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    PrefScroll->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    ResScroll->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    // TextViews
    refBuilder->get_widget("Attri_Prev", AttriView);
    refBuilder->get_widget("Constraint_Prev", ConstView);
    refBuilder->get_widget("Pref_Prev", PrefView);
    AttriView->set_buffer(AttriBuff);
    ConstView->set_buffer(ConstBuff);
    PrefView->set_buffer(PrefBuff);
    // TODO: Add treeview and plug it for results viewing
  }

  // Run the application
  app->run(*pAppWin);
  return 0;
}
