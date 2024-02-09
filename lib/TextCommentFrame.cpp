#include "TextCommentFrame.h"

tcframe::TCFrame::TCFrame(char id[4], std::ifstream& stream, uint32_t& byte_n) :
    basicframe::BasicFrame(id, stream) {
    uint32_t bytes_need = header.GetSize();
    stream.get(coding);
    stream.read(lang, 3);
    uint32_t bytes_read = 4;

    char symbol;
    bool last_was_null = false;
    bool double_null_termination = (coding == 0x1 || coding == 0x2);
    while (bytes_read < bytes_need) {
        stream.get(symbol);
        bytes_read++;
        if (!symbol && (!double_null_termination || last_was_null)) break;
        if (!symbol) last_was_null = true;
        description += symbol;
    }
    TrimString(description);
    while (bytes_read < bytes_need) {
        stream.get(symbol);
        bytes_read++;
        text += symbol;
    }
    TrimString(text);
    byte_n += bytes_read + FRAME_HEADER_SIZE;
}

void tcframe::TCFrame::Print(std::ofstream& stream) {
    stream << "\tMulti comment frame (lang. ";
    if (lang[0]) stream.write(lang, 3);
    else stream << "not available";
    stream << ") ";
    stream.write(header.GetId(), 4);
    stream << ':';
    if (!description.empty()) {
        stream << "\n\tDescription:\n\t";
        stream.write(description.c_str(), (int64_t) description.size());
    }
    if (!text.empty()) {
        stream << "\n\tText:\n\t";
        for (auto i: text) {
            stream << i;
            if (i == '\n') stream << '\t';
        }
    }
    stream << "\n\t-------------\n";
}
