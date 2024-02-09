#include "includes.h"
#include "ID3v2HeadFooter.h"


id3headfooter::HeadFooter::HeadFooter(std::ifstream& stream) {
    char id[3];
    stream.read(id, 3);
    if (strcmp(id, "ID3") != 0) throw std::runtime_error("File is not ID3 format");

    char data[7];
    stream.read(data, 7);
    version = *reinterpret_cast<uint8_t*>(&data[0]);
    subversion = *reinterpret_cast<uint8_t*>(&data[1]);
    uint8_t flags = *reinterpret_cast<uint8_t*>(&data[2]);
    unsync_enabled = flags & 0b10000000;
    extended_header_enabled = flags & 0b01000000;
    footer_enabled = flags & 0b00010000;
    size_ = ToSyncSafeInteger(&data[3]);
}

bool id3headfooter::HeadFooter::UnsyncEnabled() const {
    return unsync_enabled;
}

bool id3headfooter::HeadFooter::ExtendedHeaderEnabled() const {
    return extended_header_enabled;
}

bool id3headfooter::HeadFooter::FooterEnabled() const {
    return footer_enabled;
}

uint32_t id3headfooter::HeadFooter::GetSize() const {
    return size_;
}
