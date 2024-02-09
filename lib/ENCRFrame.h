#pragma once
#include "BasicFrame.h"

namespace encrframe {
    class ENCRFrame : public basicframe::BasicFrame {
    private:
        std::string owner_id;
        char method_symbol = '\0';
    public:
        explicit ENCRFrame(std::ifstream& stream, uint32_t& byte_n);

        void Print(std::ofstream& stream) final;
    };
}
