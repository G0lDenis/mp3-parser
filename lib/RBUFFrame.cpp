#include "RBUFFrame.h"

rbufframe::RBUFFrame::RBUFFrame(std::ifstream& stream, uint32_t& bytes_n) :
    basicframe::BasicFrame("RBUF", stream) {
    char data[4] = {'\0', '\0', '\0', '\0'};
    stream.read(&data[1], 4);
    buffer_size = *reinterpret_cast<uint32_t*>(&data[0]);
    char byte;
    stream.get(byte);
    flag = byte & 0b00000001;
    stream.read(&data[0], 4);
    offset = *reinterpret_cast<uint32_t*>(&data[0]);
    bytes_n += 8 + FRAME_HEADER_SIZE;
}

void rbufframe::RBUFFrame::Print(std::ofstream& stream) {
    stream << "\t Buffer size frame:\n\tBuffer size: " << buffer_size
           << "\n\tAdded audio stream: " << (flag? "true" : "false")
           << "\n\tOffset to next tag: " << offset;
    stream << "\n\t-------------\n";
}
