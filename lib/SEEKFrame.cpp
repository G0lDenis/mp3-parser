#include "SEEKFrame.h"

seekframe::SEEKFrame::SEEKFrame(std::ifstream& stream, uint32_t& byte_n) :
    basicframe::BasicFrame("SEEK", stream) {
    std::string str;
    char data[4];
    offset = *reinterpret_cast<uint32_t*>(&data[0]);
    byte_n += 4 + FRAME_HEADER_SIZE;
}

void seekframe::SEEKFrame::Print(std::ofstream& stream) {
    stream << "\tSeek frame: " << offset;
    stream << "\n\t-------------\n";
}
