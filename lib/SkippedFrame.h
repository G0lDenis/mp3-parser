#pragma once

#include "BasicFrame.h"

namespace skippedframe {
    class SkippedFrame : public basicframe::BasicFrame {
    public:
        explicit SkippedFrame(char id[4], std::ifstream& stream, uint32_t& byte_n);
    };
}
