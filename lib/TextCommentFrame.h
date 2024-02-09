#pragma once

#include "BasicFrame.h"

namespace tcframe {
    class TCFrame : public basicframe::BasicFrame {
    private:
        char coding = '\0';
        char lang[3] = {};
        std::string description;
        std::string text;
    public:
        explicit TCFrame(char id[4], std::ifstream& stream, uint32_t& byte_n);

        void Print(std::ofstream& stream) final;
    };
}
