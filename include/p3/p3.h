//
// Created by nolan on 3/30/22.
//

#ifndef PROJECT3_P3_H
#define PROJECT3_P3_H

#include <bitset>
#include <vector>

#define maxAttributes 10
#include "clasp/config.h"
#include <iostream>
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
void testing(void);



#endif //PROJECT3_P3_H
