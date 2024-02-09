#pragma once

#include "BasicFrame.h"

namespace usertextframe {
    class UTFrame : public basicframe::BasicFrame {
    private:
        char coding = '\0';
        std::string description;
        std::string text;
    public:
        explicit UTFrame(char id[4], std::ifstream& stream, uint32_t& byte_n);

        void Print(std::ofstream& stream) final;
    };
}
