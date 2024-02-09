#include "USERFrame.h"

userframe::USERFrame::USERFrame(std::ifstream& stream, uint32_t& byte_n) :
    basicframe::BasicFrame("USER", stream) {
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
        text += symbol;
    }
    byte_n += bytes_need + FRAME_HEADER_SIZE;
}

void userframe::USERFrame::Print(std::ofstream& stream) {
    stream << "\tTerms of user frame (lang. ";
    if (lang[0]) stream.write(lang, 3);
    else stream << "not available";
    stream << ") ";
    stream.write(header.GetId(), 4);
    stream << ':';
    if (!text.empty()) {
        stream << "\n\tText:\n\t";
        for (auto i: text) {
            stream << i;
            if (i == '\n') stream << '\t';
        }
    }
    stream << "\n\t-------------\n";
}
