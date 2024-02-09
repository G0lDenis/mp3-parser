#include "SkippedFrame.h"

skippedframe::SkippedFrame::SkippedFrame(char id[4], std::ifstream& stream, uint32_t& byte_n) :
    basicframe::BasicFrame(id, stream) {
    uint32_t bytes_need = header.GetSize();
    stream.seekg(bytes_need, std::ios_base::cur);
    byte_n += bytes_need + FRAME_HEADER_SIZE;
}
