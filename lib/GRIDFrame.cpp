#include "GRIDFrame.h"

gridframe::GRIDFrame::GRIDFrame(std::ifstream& stream, uint32_t& byte_n) :
    basicframe::BasicFrame("GRID", stream) {
    uint32_t bytes_need = header.GetSize();
    uint32_t bytes_read = 1;
    char symbol;
    while (stream.get(symbol)) {
        owner_id += symbol;
        bytes_read++;
    }
    stream.get(group_symbol);
    stream.seekg(bytes_need - bytes_read, std::ios_base::cur);
    byte_n += bytes_need + FRAME_HEADER_SIZE;
}

void gridframe::GRIDFrame::Print(std::ofstream& stream) {
    stream << "\tOwner id:\n\t" << owner_id;
    stream << "Group symbol: " << group_symbol;
    stream << "\n\t-------------\n";
}
