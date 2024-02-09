#pragma once

#include "BasicFrame.h"

namespace textframe {
    class TFrame : public basicframe::BasicFrame {
    protected:
        char coding = '\0';
        std::string info;
    public:
        explicit TFrame(char id[4], std::ifstream& stream, uint32_t& byte_n);

        void Print(std::ofstream& stream) override;
    };
}
