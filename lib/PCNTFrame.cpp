#include "PCNTFrame.h"

pcntframe::PCNTFrame::PCNTFrame(std::ifstream& stream, uint32_t& bytes_n) :
    basicframe::BasicFrame("PCNT", stream) {
    uint32_t bytes_need = header.GetSize();
    char symbol;
    std::string str;
    uint32_t bytes_read = 0;
    while (bytes_read < bytes_need) {
        stream.get(symbol);
        bytes_read++;
        str += symbol;
    }
    counter = *((uint64_t*) (str.c_str()));
    bytes_n += bytes_need + FRAME_HEADER_SIZE;
}

void pcntframe::PCNTFrame::Print(std::ofstream& stream) {
    stream << "\tPlay counter frame:\n\tPlayed for " << counter << " times";
    stream << "\n\t-------------\n";
}
