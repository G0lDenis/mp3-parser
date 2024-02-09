#pragma once

#include "BasicFrame.h"

namespace equ2frame {
    class EQU2Frame : public basicframe::BasicFrame {
    private:
        std::string method;
        std::string id;
        std::vector<std::pair<uint16_t , int16_t>> stamps;
    public:
        explicit EQU2Frame(std::ifstream& stream, uint32_t& bytes_n);

        void Print(std::ofstream& stream) final;
    };
}
