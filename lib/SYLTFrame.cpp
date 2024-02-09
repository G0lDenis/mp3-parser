#include "SYLTFrame.h"

std::map<char, std::string> content{
    {0x0, "other"},
    {0x1, "lyrics"},
    {0x2, "text transcription"},
    {0x3, "movement/part name"},
    {0x4, "event"},
    {0x5, "chord "},
    {0x6, "trivia/'pop up' information"},
    {0x7, "URL to webpage"},
    {0x8, "URL to image"}
};

syltframe::SYLTFrame::SYLTFrame(std::ifstream& stream, uint32_t& byte_n) :
    basicframe::BasicFrame("SYLT", stream) {
    uint32_t bytes_need = header.GetSize();
    stream.get(coding);
    stream.read(lang, 3);
    char ts;
    stream.get(ts);
    timestamp = (ts == 0x1 ? "f/u" : "ms");
    stream.get(content_type);
    uint32_t bytes_read = 6;
    while (bytes_read < bytes_need) {
        std::string description;
        while (stream.get(ts)) {
            bytes_read++;
            description += ts;
        }
        TrimString(description);
        stream.get(ts);
        char data[4];
        stream.read(data, 4);
        bytes_read += 5;
        sync_text.emplace_back(description, ts, *reinterpret_cast<uint32_t*>(&data[0]));
    }
    byte_n += bytes_need + FRAME_HEADER_SIZE;
}

void syltframe::SYLTFrame::Print(std::ofstream& stream) {
    stream << "\tSynchronised lyrics frame (lang. ";
    if (lang[0]) stream.write(lang, 3);
    else stream << "not available";
    stream << "):";
    for (auto& p: sync_text) {
        stream << "\n\t" << content[std::get<1>(p)] << ' ';
        stream << std::get<2>(p) << timestamp << ' ';
        stream << std::get<0>(p);
    }
    stream << "\n\t-------------\n";
}
