#include "ENCRFrame.h"

encrframe::ENCRFrame::ENCRFrame(std::ifstream& stream, uint32_t& byte_n) :
    basicframe::BasicFrame("ENCR", stream) {
    uint32_t bytes_need = header.GetSize();
    uint32_t bytes_read = 1;
    char symbol;
    while (stream.get(symbol)) {
        owner_id += symbol;
        bytes_read++;
    }
    stream.get(method_symbol);
    stream.seekg(bytes_need - bytes_read, std::ios_base::cur);
    byte_n += bytes_need + FRAME_HEADER_SIZE;
}

void encrframe::ENCRFrame::Print(std::ofstream& stream) {
    stream << "\tOwner id (ENCR)\n\t";
    stream << owner_id;
    stream << "\n\t-------------\n";
}
