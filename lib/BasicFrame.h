#pragma once

#include "FrameHeader.h"
#include <map>
#include <vector>


#define FRAME_HEADER_SIZE 10

namespace basicframe {
    class BasicFrame {
    protected:
        frameheader::FrameHeader header;

    public:
        BasicFrame(const char id[4], std::ifstream& stream);

        virtual void Print(std::ofstream& stream);
    };
}

inline std::map<char, std::vector<basicframe::BasicFrame*>> frame_groups{};
