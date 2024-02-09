#include "TextFrame.h"

textframe::TFrame::TFrame(char id[4], std::ifstream& stream, uint32_t& byte_n) :
    basicframe::BasicFrame(id, stream) {
    uint32_t bytes_need = header.GetSize();
    stream.get(coding);
    uint32_t bytes_read = 1;

    char symbol;
    while (bytes_read < bytes_need) {
        stream.get(symbol);
        bytes_read++;
        info += symbol;
    }
    TrimString(info);
    stream.seekg(bytes_need - bytes_read, std::ios_base::cur);
    byte_n += bytes_need + FRAME_HEADER_SIZE;
}

void textframe::TFrame::Print(std::ofstream& stream) {
    stream << "\tText frame ";
    stream.write(header.GetId(), 4);
    stream << ":\n\t";
    stream << info;
    stream << "\n\t-------------\n";
}
