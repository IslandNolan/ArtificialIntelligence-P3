#ifndef PROJECT3_P3_H
#define PROJECT3_P3_H

#include <bitset>
#include <vector>

#define maxAttributes 10
#include <iostream>
#include <unordered_map>

#include <gtkmm-3.0/gtkmm.h>
#include <gtkmm-3.0/gtkmm/applicationwindow.h>
#include <gtkmm-3.0/gtkmm/builder.h>

namespace p3 {
    class utility;
    class App;
    class main;
}

Glib::RefPtr<Gtk::TextBuffer> getAttriBuff();
void BufferFlush(Glib::RefPtr<Gtk::TextBuffer> buff);
int wininit(int argc, char **argv);
int checkOr(std::bitset<maxAttributes> toCheck, std::vector<std::vector<std::pair<int, int>>> values);
int checkAnd(std::bitset<maxAttributes> toCheck, std::vector<std::pair<int, int>> values);
void testing();
void testing2(std::vector<std::vector<std::pair<int,int>>> hardConstraints);
std::vector<std::vector<std::string>> penaltiesFunction(std::unordered_map<std::string, std::pair<std::string,std::string>> attributeNames, std::vector<std::string> penaltyStrings, std::vector<int> blacklist, std::vector<std::vector<std::pair<int,int>>> penalties, std::vector<int> penaltyStack, std::vector<int> penaltyCosts);
std::vector<std::vector<std::string>> possibilisticFunction(std::unordered_map<std::string, std::pair<std::string,std::string>> attributeNames, std::vector<std::string> penaltyStrings, std::vector<int> blacklist, std::vector<std::vector<std::pair<int,int>>> penalties, std::vector<int> penaltyStack, std::vector<int> penaltyCosts);
std::vector<std::vector<std::string>> qualitativeFunction(std::unordered_map<std::string, std::pair<std::string,std::string>> attributeNames, std::vector<std::string> penaltyStrings, std::vector<int> blacklist, std::vector<std::vector<std::pair<int,int>>> penalties, std::vector<int> penaltyStack, std::vector<int> penaltyCosts, std::vector<int> qualitativeColumn, std::vector<int> qualitativeCost);
std::vector<int> blacklistFunction(int attributeCount, std::vector<std::vector<std::pair<int,int>>> hardConstraints);
void parseAttributes(std::string fileName);
void parseConstraints(std::string fileName);
void BufferInsert(Glib::RefPtr<Gtk::TextBuffer> buff, std::string data);
void logicProcessing(int, std::string fileName);
void startProcessing(int which);
std::vector<std::vector<std::string>> feasbility(std::vector<std::vector<std::string>> matrix, int which);
#endif //PROJECT3_P3_H
