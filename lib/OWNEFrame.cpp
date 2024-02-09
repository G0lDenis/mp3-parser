#include "OWNEFrame.h"

owneframe::OWNEFrame::OWNEFrame(std::ifstream& stream, uint32_t& byte_n) :
    basicframe::BasicFrame("OWNE", stream) {
    uint32_t bytes_need = header.GetSize();
    stream.get(coding);
    uint32_t bytes_read = 2;
    char symbol;
    while (stream.get(symbol)) {
        bytes_read++;
        price += symbol;
    }
    char data[8];
    stream.read(data, 8);
    bytes_read += 8;
    for (auto i = 0; i < 4; i++) {
        date += data[i];
    }
    date += '-';
    for (auto i = 4; i < 6; i++) {
        date += data[i];
    }
    date += '-';
    for (auto i = 6; i < 8; i++) {
        date += data[i];
    }
    while (bytes_read < bytes_need) {
        stream.get(symbol);
        bytes_read++;
        seller += symbol;
    }
    TrimString(seller);
    byte_n += bytes_read + FRAME_HEADER_SIZE;

}

void owneframe::OWNEFrame::Print(std::ofstream& stream) {
    stream << "\tOwnership frame:\n\tBought on " << date << " by " << seller << " for " << price;
    stream << "\n\t-------------\n";
}
