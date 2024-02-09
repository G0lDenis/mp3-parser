#include "ETCOFrame.h"

std::map<char,std::string> types{
    {0x0, "padding (has no meaning)"},
    {0x1, "end of initial silence"},
    {0x2, "intro start"},
    {0x3, "main part start"},
    {0x4, "outro start"},
    {0x5, "outro end"},
    {0x6, "verse start"},
    {0x7, "refrain start"},
    {0x8, "interlude start"},
    {0x9, "theme start"},
    {0xA, "variation start"},
    {0xB, "key change"},
    {0xC, "time change"},
    {0xD, "momentary unwanted noise (Snap, Crackle & Pop)"},
    {0xE, "sustained noise"},
    {0xF, "sustained noise end"},
    {0x10, "intro end"},
    {0x11, "main part end"},
    {0x12, "verse end"},
    {0x13, "refrain end"},
    {0x14, "theme end"},
    {0x15, "profanity"},
    {0x16, "profanity end"},
    {0xFD, "audio end (start of silence)"},
    {0xFE, "audio file ends"}
};

etcoframe::ETCOFrame::ETCOFrame(std::ifstream& stream, uint32_t& bytes_n) :
    basicframe::BasicFrame("ETCO", stream) {
    uint32_t bytes_need = header.GetSize();
    char ts;
    stream.get(ts);
    timestamp = (ts == 0x1 ? "f/u" : "ms");
    uint32_t bytes_read = 0;
    while (bytes_read < bytes_need) {
        stream.get(ts);
        char data[4];
        stream.read(data, 4);
        stamps.emplace_back(ts, *reinterpret_cast<uint32_t*>(&data[0]));
        bytes_read += 5;
    }
    bytes_n += bytes_need + FRAME_HEADER_SIZE;
}

void etcoframe::ETCOFrame::Print(std::ofstream& stream) {
    stream << "\tTime codes frame data:";
    for (auto& p: stamps) {
        stream << "\n\t" << types[p.first] << ' ' << p.second << timestamp;
    }
    stream << "\n\t-------------\n";
}
