#pragma once

#include "BasicFrame.h"

namespace etcoframe {
    class ETCOFrame : public basicframe::BasicFrame {
    private:
        std::string timestamp;
        std::vector<std::pair<char, uint32_t>> stamps;
    public:
        explicit ETCOFrame(std::ifstream& stream, uint32_t& bytes_n);

        void Print(std::ofstream& stream) final;
    };
}
