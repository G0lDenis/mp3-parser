#pragma once

#include "BasicFrame.h"

namespace ufidframe {
    class UFIDnPRIVFrame : public basicframe::BasicFrame {
    private:
        std::string owner_id;
    public:
        explicit UFIDnPRIVFrame(char id[4], std::ifstream& stream, uint32_t& byte_n);

        void Print(std::ofstream& stream) final;
    };
}
