#pragma once

#include "BasicFrame.h"

namespace comrframe {
    class COMRFrame : public basicframe::BasicFrame {
    private:
        char coding = '\0';
        std::string price;
        std::string date;
        std::string contact;
        char received = '\0';
        std::string seller;
        std::string description;
        std::string image_type;
    public:
        explicit COMRFrame(std::ifstream& stream, uint32_t& byte_n);

        void Print(std::ofstream& stream) final;
    };
}
