#pragma once

#include "BasicFrame.h"

namespace pcntframe {
    class PCNTFrame : public basicframe::BasicFrame {
    private:
        uint64_t counter;
    public:
        explicit PCNTFrame(std::ifstream& stream, uint32_t& bytes_n);

        void Print(std::ofstream& stream) final;
    };
}
