#include "clasp/config.h"
#include <iostream>
namespace Clasp {
    struct Model;
    class  OutputTable;
    namespace Asp { class  LogicProgram; }
}
void printModel(const Clasp::OutputTable& out, const Clasp::Model& model);
void addSimpleProgram(Clasp::Asp::LogicProgram& prg);