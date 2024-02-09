#include "POPMFrame.h"

popmframe::POPMFrame::POPMFrame(std::ifstream& stream, uint32_t& byte_n) :
    basicframe::BasicFrame("POPM", stream) {
    uint32_t bytes_need = header.GetSize();
    uint32_t bytes_read = 2;

    char symbol;
    while (stream.get(symbol) && symbol) {
        bytes_read++;
        mail += symbol;
    }
    stream.get(rating);
    std::string str;
    while (bytes_read < bytes_need) {
        stream.get(symbol);
        bytes_read++;
        str += symbol;
    }
    counter = *((uint64_t*) (str.c_str()));
    byte_n += bytes_need + FRAME_HEADER_SIZE;
}

void popmframe::POPMFrame::Print(std::ofstream& stream) {
    stream << "\tPopularimeter frame:\n\tUser email:\n\t" << mail;
    stream << "\n\tRating: " << (uint8_t) rating - '\0';
    if (counter != 0) {
        stream << "\n\tCounter: \n\t" << counter;
    }
    stream << "\n\t-------------\n";
}
