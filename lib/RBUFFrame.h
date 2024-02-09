#pragma once

#include "BasicFrame.h"

namespace rbufframe {
    class RBUFFrame : public basicframe::BasicFrame {
    private:
        uint32_t buffer_size;
        bool flag;
        uint32_t offset;
    public:
        explicit RBUFFrame(std::ifstream& stream, uint32_t& bytes_n);

        void Print(std::ofstream& stream) final;
    };
}
