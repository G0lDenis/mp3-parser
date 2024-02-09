#include "EQU2Frame.h"

equ2frame::EQU2Frame::EQU2Frame(std::ifstream& stream, uint32_t& bytes_n) :
    basicframe::BasicFrame("EQU2", stream) {
    uint32_t bytes_need = header.GetSize();
    char byte;
    stream.get(byte);
    method = (byte == 0x0 ? "No interpolation" : "Linear interpolation");
    uint32_t bytes_read = 0;
    while (stream.get(byte)) {
        bytes_read++;
        id += byte;
    }
    TrimString(id);
    while (bytes_read < bytes_need) {
        char data[2];
        stream.read(&data[0], 2);
        uint16_t freq = *reinterpret_cast<uint16_t*>(&data[0]);
        stream.read(&data[0], 2);
        uint16_t volume = *reinterpret_cast<int16_t*>(&data[0]);
        stamps.emplace_back(freq, volume);
        bytes_read += 4;
    }
    bytes_n += bytes_need + FRAME_HEADER_SIZE;
}

void equ2frame::EQU2Frame::Print(std::ofstream& stream) {
    stream << "\t Equalisation (2) frame with interpolation method " << method
           << "\n\t" << "ID: " << id;
    for (auto& p: stamps) {
        stream << "\n\tfreq: " << p.first << ", va: " << p.second;
    }
    stream << "\n\t-------------\n";
}
