#pragma once

#include "BasicFrame.h"

namespace popmframe {
    class POPMFrame : public basicframe::BasicFrame {
    private:
        std::string mail;
        char rating = '\0';
        uint64_t counter;
    public:
        explicit POPMFrame(std::ifstream& stream, uint32_t& byte_n);

        void Print(std::ofstream& stream) final;
    };
}
