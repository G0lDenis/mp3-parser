#pragma once

#include "BasicFrame.h"

namespace gridframe {
    class GRIDFrame : public basicframe::BasicFrame {
    private:
        std::string owner_id;
        char group_symbol = '\0';
    public:
        explicit GRIDFrame(std::ifstream& stream, uint32_t& byte_n);

        void Print(std::ofstream& stream) final;
    };
}
