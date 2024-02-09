#pragma once

#include "BasicFrame.h"

namespace webframe {
    class WebFrame : public basicframe::BasicFrame {
    private:
        std::string link;
    public:
        explicit WebFrame(char id[4], std::ifstream& stream, uint32_t& byte_n);

        void Print(std::ofstream& stream) final;
    };
}