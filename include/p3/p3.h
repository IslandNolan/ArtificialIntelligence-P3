#ifndef PROJECT3_P3_H
#define PROJECT3_P3_H

#include <bitset>
#include <vector>

#define maxAttributes 10
#include "clasp/config.h"
#include <iostream>
#include <unordered_map>

namespace Clasp {
    struct Model;
    class  OutputTable;
    namespace Asp { class  LogicProgram; }
}
namespace p3 {
    class utility;
}
void printModel(const Clasp::OutputTable& out, const Clasp::Model& model);
void addSimpleProgram(Clasp::Asp::LogicProgram& prg);
int checkOr(std::bitset<maxAttributes> toCheck, std::vector<std::vector<std::pair<int, int>>> values);
int checkAnd(std::bitset<maxAttributes> toCheck, std::vector<std::pair<int, int>> values);
void testing();
void testing2(std::vector<std::vector<std::pair<int,int>>> hardConstraints);
void penaltiesFunction(std::unordered_map<std::string, std::pair<std::string,std::string>> attributeNames, std::vector<int> blacklist, std::vector<std::vector<std::pair<int,int>>> penalties, std::vector<int> penaltyStack, std::vector<int> penaltyCosts);
std::vector<int> blacklistFunction(int attributeCount, std::vector<std::vector<std::pair<int,int>>> hardConstraints);


#endif //PROJECT3_P3_H
