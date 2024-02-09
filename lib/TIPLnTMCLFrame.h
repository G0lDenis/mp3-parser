#pragma once

#include "TextFrame.h"

namespace tiplntmclframe {
    class TIPLnTMCLFrame : public textframe::TFrame {
    public:
        explicit TIPLnTMCLFrame(char id[4], std::ifstream& stream, uint32_t& byte_n);

        void Print(std::ofstream& stream) final;
    };
}
