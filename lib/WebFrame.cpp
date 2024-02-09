#include "WebFrame.h"

webframe::WebFrame::WebFrame(char id[4], std::ifstream& stream, uint32_t& byte_n) :
    basicframe::BasicFrame(id, stream) {
    uint32_t bytes_need = header.GetSize();
    uint32_t bytes_read = 0;
    char symbol;
    while (bytes_read < bytes_need) {
        stream.get(symbol);
        bytes_read++;
        link += symbol;
    }
    TrimString(link);
    byte_n += bytes_read + FRAME_HEADER_SIZE;
}

void webframe::WebFrame::Print(std::ofstream& stream) {
    stream << "\tMultiComment frame:\n\t" << link;
    stream << "\n\t-------------\n";
}
