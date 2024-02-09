#pragma once
#include "includes.h"

#define HEAD_FOOTER_SIZE 10


namespace id3headfooter {
    class HeadFooter {
    private:
        uint8_t version;
        uint8_t subversion;
        uint32_t size_;
        bool unsync_enabled;
        bool extended_header_enabled;
        bool footer_enabled;
    public:
        explicit HeadFooter(std::ifstream& stream);

        bool UnsyncEnabled() const;

        bool ExtendedHeaderEnabled() const;

        bool FooterEnabled() const;

        uint32_t GetSize() const;
    };
}
