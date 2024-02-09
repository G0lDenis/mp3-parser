#include "UFIDnPRIVFrame.h"


ufidframe::UFIDnPRIVFrame::UFIDnPRIVFrame(char id[4], std::ifstream& stream, uint32_t& byte_n) :
    basicframe::BasicFrame(id, stream) {
    uint32_t bytes_need = header.GetSize();
    uint32_t bytes_read = 0;
    char symbol;
    while (bytes_read < bytes_need && stream.get(symbol)) {
        owner_id += symbol;
        bytes_read++;
    }
    stream.seekg(bytes_need - bytes_read, std::ios_base::cur);
    byte_n += bytes_need + FRAME_HEADER_SIZE;
}

void ufidframe::UFIDnPRIVFrame::Print(std::ofstream& stream) {
    stream << "\tOwner id (";
    stream.write(header.GetId(), 4);
    stream <<"):\n\t";
    stream << owner_id;
    stream << "\n\t-------------\n";
}
