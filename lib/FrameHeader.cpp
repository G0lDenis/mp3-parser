#include "FrameHeader.h"


frameheader::FrameHeader::FrameHeader(const char id[4], std::ifstream& stream) {
    strncpy(id_, id, 4);

    char data[6];
    stream.read(data, 6);

    size_ = ToSyncSafeInteger(&data[0]);
    uint8_t flags = *reinterpret_cast<uint8_t*>(&data[5]);
    is_in_group_ = flags & 0b10000000;
    unsync_enabled_ = flags & 0b00000010;
    has_data_length_indicator_ = flags & 0b00000001;
}

char frameheader::FrameHeader::GetGroup() const {
    return group_;
}

bool frameheader::FrameHeader::UnsyncEnabled() const {
    return unsync_enabled_;
}

bool frameheader::FrameHeader::HasDataLengthIndicator() const {
    return has_data_length_indicator_;
}

uint32_t frameheader::FrameHeader::GetSize() const {
    return size_;
}

const char* frameheader::FrameHeader::GetId() const {
    return id_;
}
