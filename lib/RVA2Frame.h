#pragma once

#include "BasicFrame.h"

namespace rva2frame {
    class RVA2Frame : public basicframe::BasicFrame {
    private:
        std::string info;
        std::vector<std::tuple<char, int16_t, uint32_t>> channels;
    public:
        explicit RVA2Frame(std::ifstream& stream, uint32_t& byte_n);

        void Print(std::ofstream& stream) final;
    };
}
