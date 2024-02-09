#include "TIPLnTMCLFrame.h"

tiplntmclframe::TIPLnTMCLFrame::TIPLnTMCLFrame(char* id, std::ifstream& stream, uint32_t& byte_n) :
    textframe::TFrame::TFrame(id, stream, byte_n) {}

void tiplntmclframe::TIPLnTMCLFrame::Print(std::ofstream& stream) {
    stream << "\tText frame ";
    stream.write(header.GetId(), 4);
    stream << ":\n\t";
    bool space = false;
    for (auto i: info) {
        if (i) stream << i;
        else {
            stream << (space ? ' ' : '-');
            space = !space;
        }
    }
    stream << "\n\t-------------\n";
}
