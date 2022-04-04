#include "p3/p3.h"

Glib::RefPtr<Gtk::TextBuffer> AttriBuff, ConstBuff, PrefBuff, ResultBuff, StatusBuff;
// Buffers for each kind of data to display to be sent to a text or tree view
Glib::RefPtr<Gtk::TextBuffer> getAttriBuff() { return AttriBuff; }
Glib::RefPtr<Gtk::TextBuffer> getConstBuff() { return ConstBuff; }
Glib::RefPtr<Gtk::TextBuffer> getPrefBuff() { return PrefBuff; }
Glib::RefPtr<Gtk::TextBuffer> getResultBuff() { return ResultBuff; }
Glib::RefPtr<Gtk::TextBuffer> getStatusBuff() { return StatusBuff; }

bool init = false;
void initBuffers() {

  std::cout << "INITALIZING BUFFERS" << std::endl;
  AttriBuff = Gtk::TextBuffer::create();
  ConstBuff = Gtk::TextBuffer::create();
  PrefBuff = Gtk::TextBuffer::create();
  ResultBuff = Gtk::TextBuffer::create();
  StatusBuff = Gtk::TextBuffer::create();
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
