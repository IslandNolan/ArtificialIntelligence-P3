#include <bitset>
#include <vector>
#include <random>
#include <bits/stdc++.h>
#include <iostream>
#include <unordered_map>
#include <gtk/gtk.h>
#include <gtkmmconfig.h>
#include <gtkmm-3.0/gtkmm/applicationwindow.h>
#include <gtkmm-3.0/gtkmm/builder.h>
#include <gtkmm-3.0/gtkmm/enums.h>
#include <gtkmm-3.0/gtkmm/textview.h>
#include <iostream>
#include <gtkmm/button.h>
#include <gtkmm/filechooserdialog.h>

#ifndef PROJECT3_P3_H
#define PROJECT3_P3_H
#define maxAttributes 10


namespace p3 {
    class utility;
    class App;
    class main;
    class File;
    class Wigets;
}
//App.cpp
int wininit(int argc, char **argv);
//Wigets.cpp
Glib::RefPtr<Gtk::TextBuffer> getAttriBuff();
Glib::RefPtr<Gtk::TextBuffer> getConstBuff();
Glib::RefPtr<Gtk::TextBuffer> getPrefBuff();
Glib::RefPtr<Gtk::TextBuffer> getResultBuff();
Glib::RefPtr<Gtk::TextBuffer> getStatusBuff();
Gtk::TextView *getAttriView();
Gtk::TextView *getConstView();
Gtk::TextView *getPrefView();
Gtk::TextView *getResultView();

void BufferFlush(Glib::RefPtr<Gtk::TextBuffer> buff);
void BufferInsert(Glib::RefPtr<Gtk::TextBuffer> buff, std::string data);
void BufferTestInit();
void initBuffers();
//File.cpp
void onConstraintsUpload();
void onPenaltyFileUpload();
void onPossibilisticUpload();
void onQualitativeUpload();
void onAttributeUpload();
//utility.cpp
int checkOr(std::bitset<maxAttributes> toCheck, std::vector<std::vector<std::pair<int, int>>> values);
int checkAnd(std::bitset<maxAttributes> toCheck, std::vector<std::pair<int, int>> values);
void testing();
void testing2(std::vector<std::vector<std::pair<int,int>>> hardConstraints);
std::vector<std::vector<std::string>> penaltiesFunction(std::unordered_map<std::string, std::pair<std::string,std::string>> attributeNames, std::vector<std::string> penaltyStrings, std::vector<int> blacklist, std::vector<std::vector<std::pair<int,int>>> penalties, std::vector<int> penaltyStack, std::vector<int> penaltyCosts);
std::vector<std::vector<std::string>> possibilisticFunction(std::unordered_map<std::string, std::pair<std::string,std::string>> attributeNames, std::vector<std::string> penaltyStrings, std::vector<int> blacklist, std::vector<std::vector<std::pair<int,int>>> penalties, std::vector<int> penaltyStack, std::vector<int> penaltyCosts);
std::vector<std::vector<std::string>> qualitativeFunction(std::unordered_map<std::string, std::pair<std::string,std::string>> attributeNames, std::vector<std::string> penaltyStrings, std::vector<int> blacklist, std::vector<std::vector<std::pair<int,int>>> penalties, std::vector<int> penaltyStack, std::vector<int> penaltyCosts, std::vector<int> qualitativeColumn, std::vector<int> qualitativeCost);
std::vector<int> blacklistFunction(int attributeCount, std::vector<std::vector<std::pair<int,int>>> hardConstraints);
std::vector<std::vector<std::string>> feasbility(std::vector<std::vector<std::string>> matrix, int which);
std::vector<std::vector<std::string>> exemplification(std::vector<std::vector<std::string>> matrix, int which);
std::vector<std::vector<std::string>> optimization(std::vector<std::vector<std::string>> matrix, int which);
std::vector<std::vector<std::string>> omniOptimization(std::vector<std::vector<std::string>> matrix, int which);
//Main.cpp
void setSelectedPref(bool x);
void setLoadedAttri(bool x);
bool getSelectedPref();
bool getLoadedAttri();
void parseAttributes(std::string fileName);
void parseConstraints(std::string fileName);
void logicProcessing(int, std::string fileName);
void startProcessing(int which);
void bufferFeasability();
void bufferExemplification();
void bufferOptimization();
void bufferOmniOptimization();
void selected(int which);

#endif //PROJECT3_P3_H
