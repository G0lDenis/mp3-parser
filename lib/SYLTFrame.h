#pragma once

#include "BasicFrame.h"

namespace syltframe {
    class SYLTFrame : public basicframe::BasicFrame {
    private:
        char coding = '\0';
        char lang[3] = {};
        std::string timestamp;
        char content_type = '\0';
        std::vector<std::tuple<std::string, char, uint32_t>> sync_text;
    public:
        explicit SYLTFrame(std::ifstream& stream, uint32_t& byte_n);

        void Print(std::ofstream& stream) final;
    };
}
