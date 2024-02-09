#pragma once

#include "BasicFrame.h"

namespace possframe {
    class POSSFrame : public basicframe::BasicFrame {
    private:
        std::string timestamp;
        uint64_t position;
    public:
        explicit POSSFrame(std::ifstream& stream, uint32_t& bytes_n);

        void Print(std::ofstream& stream) final;
    };
}
