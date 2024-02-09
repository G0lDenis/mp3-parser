#pragma once

#include "includes.h"

namespace frameheader {
    class FrameHeader {
    private:
        char id_[4]{};
        uint32_t size_{};
        bool is_in_group_{};
        bool unsync_enabled_{};
        bool has_data_length_indicator_{};
        char group_{'\0'};
    public:
        explicit FrameHeader(const char id[4], std::ifstream& stream);

        [[nodiscard]] char GetGroup() const;

        [[nodiscard]] bool UnsyncEnabled() const;

        [[nodiscard]] bool HasDataLengthIndicator() const;

        [[nodiscard]] uint32_t GetSize() const;

        [[nodiscard]] const char* GetId() const;
    };
}
