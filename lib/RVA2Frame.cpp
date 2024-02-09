#include "RVA2Frame.h"
#include <cmath>

std::map<char, std::string> channel_type{
    {0x0, "Other"},
    {0x1, "Master volume"},
    {0x2, "Front right"},
    {0x3, "Front left"},
    {0x4, "Back right"},
    {0x5, "Back left"},
    {0x6, "Front center"},
    {0x7, "Back center"},
    {0x8, "Subwoofer"}
};


rva2frame::RVA2Frame::RVA2Frame(std::ifstream& stream, uint32_t& byte_n) :
    basicframe::BasicFrame("RVA2", stream) {
    uint32_t bytes_need = header.GetSize();
    uint32_t bytes_read = 0;

    char symbol;
    while (stream.get(symbol)) {
        bytes_read++;
        info += symbol;
    }
    TrimString(info);
    for (auto i = 0; i < 8; i++) {
        std::tuple<char, int16_t, uint32_t> tp = {};
        stream.get(std::get<0>(tp));
        char data[4];
        stream.read(&data[0], 2);
        std::get<1>(tp) = *reinterpret_cast<int16_t*>(&data[0]);
        stream.get(data[0]);
        auto bytes_for_volume = (uint8_t) std::ceil((float) *reinterpret_cast<uint8_t*>(&data[0]) / 8);
        char data2[4] = {'\0', '\0', '\0', '\0'};
        stream.read(&data2[0], bytes_for_volume);
        std::get<2>(tp) = *reinterpret_cast<uint32_t*>(&data2[0]);
        channels.emplace_back(tp);
    }
    byte_n += bytes_need + FRAME_HEADER_SIZE;
}

void rva2frame::RVA2Frame::Print(std::ofstream& stream) {
    stream << "Volume adjustment frame:\n\t" << info;
    for (auto& p: channels) {
        stream << "\n\t" << channel_type[std::get<0>(p)]
               << " va: " << std::get<1>(p)
               << "db, peak: " << std::get<2>(p) << "db";
    }
    stream << "\n\t-------------\n";
}
