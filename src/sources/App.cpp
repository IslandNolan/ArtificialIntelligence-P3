#include "p3/p3.h"
#include <glibmm/refptr.h>
//#include <gtkmm-3.0/gtkmm.h>
#include <gtkmm-3.0/gtkmm/applicationwindow.h>
#include <gtkmm-3.0/gtkmm/builder.h>
#include <gtkmm-3.0/gtkmm/dialog.h>
#include <gtkmm-3.0/gtkmm/enums.h>
#include <gtkmm-3.0/gtkmm/filechooser.h>
#include <gtkmm-3.0/gtkmm/filechooserdialog.h>
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

// Buffers for each kind of data to display to be sent to a text or tree view
Glib::RefPtr<Gtk::TextBuffer> AttriBuff, ConstBuff, PrefBuff, ResultBuff;
Glib::RefPtr<Gtk::TextBuffer> getAttriBuff() { return AttriBuff; }
Glib::RefPtr<Gtk::TextBuffer> getConstBuff() { return ConstBuff; }
Glib::RefPtr<Gtk::TextBuffer> getPrefBuff() { return PrefBuff; }
Glib::RefPtr<Gtk::TextBuffer> getResultBuff() { return ResultBuff; }

// TODO: turn Attriview into a tree view
//  The different view to display the text buffers
Gtk::TextView *AttriView = nullptr, *ConstView = nullptr, *PrefView = nullptr, *ResultView = nullptr;

Gtk::ScrolledWindow *AttriScroll = nullptr, *ConstScroll = nullptr,
                    *PrefScroll = nullptr, *ResScroll = nullptr;
bool init = false;

void initBuffers() {

  std::cout << "INITALIZING BUFFERS" << std::endl;
  AttriBuff = Gtk::TextBuffer::create();
  ConstBuff = Gtk::TextBuffer::create();
  PrefBuff = Gtk::TextBuffer::create();
  ResultBuff = Gtk::TextBuffer::create();
  init = true;
}
void BufferTestInit() {
  if (!init) {
    std::cout << "BUFFERS NOT INITALIZED" << std::endl;
    return;
  } else {
      AttriBuff->set_text("AttriBuff Working!");
      ConstBuff->set_text("ConstBuff Working!");
      PrefBuff->set_text("PrefBuff Working!");
      ResultBuff->set_text("ResultBuff Working!");
  }
}
void BufferInsert(Glib::RefPtr<Gtk::TextBuffer> buff, std::string data) {
  if (!init) {
    std::cout << "buffers not initalized" << std::endl;
    return;
  } else {
    buff->insert(buff->end(), data);
  }
}
void BufferFlush(Glib::RefPtr<Gtk::TextBuffer> buff) {
  if (!init) {
    std::cout << "buffers not initalized" << std::endl;
    return;
  } else {

    std::cout << "FLUSHING BUFFER" << std::endl;
    buff->erase(buff->begin(), buff->end());
  }
}
void onConstraintsUpload() {
  Gtk::FileChooserDialog dialog("Select Constraints File",
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
        parseConstraints(filename);
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
void onAttributeUpload() {
  Gtk::FileChooserDialog dialog("Select Attributes File",
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
    parseAttributes(dialog.get_filename());
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
void onPenaltyFileUpload() {
  selected(0);
  Gtk::FileChooserDialog dialog("Select Penalty File",
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
    logicProcessing(0, filename);
    startProcessing(0);
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
void onPossibilisticUpload() {
    selected(1);
    Gtk::FileChooserDialog dialog("Select Possibilistics File",
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
            logicProcessing(1, filename);
            startProcessing(1);
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
void onQualitativeUpload() {
    selected(2);
  Gtk::FileChooserDialog dialog("Select Qualitative File",
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
    logicProcessing(2, filename);
    startProcessing(2);
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
    // AttriBuff = Gtk::TextBuffer::create();
    // AttriBuff->set_text("AttriBuff working");
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
        files.pPossL->signal_clicked().connect(sigc::ptr_fun(onPossibilisticUpload));
        files.pQual->signal_clicked().connect(sigc::ptr_fun(onQualitativeUpload));
        // TODO: have manual buttons append text to their buffers

        // Connections to the 4 functional buttons
        fun.Omniopt->signal_clicked().connect(sigc::ptr_fun(onOmniClick));
        fun.Opt->signal_clicked().connect(sigc::ptr_fun(onOptiClick));
        fun.Exemp->signal_clicked().connect(sigc::ptr_fun(onExemClick));
        fun.Feas->signal_clicked().connect(sigc::ptr_fun(onFeasClick));

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
        refBuilder->get_widget("Const_Prev", ConstView);
        refBuilder->get_widget("Pref_Prev", PrefView);
        refBuilder->get_widget("Res_View", ResultView);

        AttriView->set_buffer(AttriBuff);
        ConstView->set_buffer(ConstBuff);
        PrefView->set_buffer(PrefBuff);
        ResultView->set_buffer(ResultBuff);

    }

    // Run the application
    app->run(*pAppWin);
    return 0;
}
