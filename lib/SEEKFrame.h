#pragma once

#include "BasicFrame.h"

namespace seekframe {
    class SEEKFrame : public basicframe::BasicFrame {
    private:
        uint32_t offset;
    public:
        explicit SEEKFrame(std::ifstream& stream, uint32_t& byte_n);

        void Print(std::ofstream& stream) final;
    };
}
