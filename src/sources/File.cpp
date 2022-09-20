#include "p3/p3.h"

void onConstraintsUpload() {
    if(!getLoadedAttri()) {
        BufferFlush(getStatusBuff());
        BufferInsert(getStatusBuff(),"Missing Attributes File");
        return;
    }
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
            BufferFlush(getStatusBuff());
            BufferInsert(getStatusBuff(),"Imported Attributes");
            setLoadedAttri(true);
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
    if (!getLoadedAttri()) {
        BufferFlush(getStatusBuff());
        BufferInsert(getStatusBuff(), "Missing Attributes File");
        return;
    }

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
            BufferFlush(getStatusBuff());
            BufferInsert(getStatusBuff(),"Imported Penalties");
            setSelectedPref(true);
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
    if(!getLoadedAttri()) {
        BufferFlush(getStatusBuff());
        BufferInsert(getStatusBuff(),"Missing Attributes File");
        return;
    }
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
            BufferFlush(getStatusBuff());
            BufferInsert(getStatusBuff(),"Imported Possibilistics");
            setSelectedPref(true);
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
    if(!getLoadedAttri()) {
        BufferFlush(getStatusBuff());
        BufferInsert(getStatusBuff(),"Missing Attributes File..");
        return;
    }
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
            BufferFlush(getStatusBuff());
            BufferInsert(getStatusBuff(),"Imported Qualitative");
            setSelectedPref(true);
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
