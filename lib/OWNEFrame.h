#pragma once

#include "BasicFrame.h"

namespace owneframe {
    class OWNEFrame : public basicframe::BasicFrame {
    private:
        char coding = '\0';
        std::string price;
        std::string date;
        std::string seller;
    public:
        explicit OWNEFrame(std::ifstream& stream, uint32_t& byte_n);

        void Print(std::ofstream& stream) final;
    };
}
