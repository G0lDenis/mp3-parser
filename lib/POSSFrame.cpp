#include "POSSFrame.h"

possframe::POSSFrame::POSSFrame(std::ifstream& stream, uint32_t& bytes_n) :
    basicframe::BasicFrame("POSS", stream) {
    uint32_t bytes_need = header.GetSize();
    char byte;
    stream.get(byte);
    timestamp = (byte == 0x1 ? "f/u" : "ms");
    uint32_t bytes_read = 1;
    std::string str;
    while (bytes_read < bytes_need) {
        stream.get(byte);
        bytes_read++;
        str += byte;
    }
    position = *((uint64_t*) (str.c_str()));
    bytes_n += bytes_need + FRAME_HEADER_SIZE;
}

void possframe::POSSFrame::Print(std::ofstream& stream) {
    stream << "\tPosition sync frame:\n\tPosition: " << position << timestamp;
    stream << "\n\t-------------\n";
}
