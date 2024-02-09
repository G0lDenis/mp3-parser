#include "COMRFrame.h"

std::map<char, std::string> receive_types{
    {0x0, "Other"},
    {0x1, "Standard CD album with other songs"},
    {0x2, "Compressed audio on CD"},
    {0x3, "File over the Internet"},
    {0x4, "Stream over the Internet"},
    {0x5, "As note sheets"},
    {0x6, "As note sheets in a book with other sheets"},
    {0x7, "Music on other media"},
    {0x8, "Non-musical merchandise"}
};

comrframe::COMRFrame::COMRFrame(std::ifstream& stream, uint32_t& byte_n) :
    basicframe::BasicFrame("COMR", stream) {
    uint32_t bytes_need = header.GetSize();
    stream.get(coding);
    uint32_t bytes_read = 1;
    char symbol;
    while (stream.get(symbol)) {
        bytes_read++;
        price += symbol;
    }
    bytes_read++;
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
    while (stream.get(symbol)) {
        bytes_read++;
        contact += symbol;
    }
    bytes_read += 2;
    stream.get(received);
    bool last_was_null = false;
    bool double_null_termination = (coding == 0x1 || coding == 0x2);
    while (bytes_read < bytes_need) {
        stream.get(symbol);
        bytes_read++;
        if (!symbol && (!double_null_termination || last_was_null)) break;
        if (!symbol) last_was_null = true;
        seller += symbol;
    }
    TrimString(seller);
    last_was_null = false;
    while (bytes_read < bytes_need) {
        stream.get(symbol);
        bytes_read++;
        if (!symbol && (!double_null_termination || last_was_null)) break;
        if (!symbol) last_was_null = true;
        description += symbol;
    }
    TrimString(description);
    while (stream.get(symbol)) {
        bytes_read++;
        image_type += symbol;
    }
    byte_n += bytes_need + FRAME_HEADER_SIZE;
}

void comrframe::COMRFrame::Print(std::ofstream& stream) {
    stream << "\tCommercial information frame:\n"
           << "\tPrice: " << price << '\n'
           << "\tValid until " << date << '\n'
           << "\tContact URL: " << contact << '\n'
           << "\tReceiving type: " << receive_types[received] << '\n'
           << "\tSeller: " << seller << '\n'
           << "\tDescription: " << description << '\n'
           << "\tPicture MIME type: " << image_type
           << "\n\t-------------\n";
}
