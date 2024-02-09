#pragma once

#include "BasicFrame.h"

namespace userframe {
    class USERFrame : public basicframe::BasicFrame {
    private:
        char coding = '\0';
        char lang[3] = {};
        std::string text;
    public:
        explicit USERFrame(std::ifstream& stream, uint32_t& byte_n);

        void Print(std::ofstream& stream) final;
    };
}
