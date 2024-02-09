#include "BasicFrame.h"

basicframe::BasicFrame::BasicFrame(const char id[4], std::ifstream& stream) :
    header(id, stream) {
    if (frame_groups.contains(header.GetGroup()))
        frame_groups[header.GetGroup()].emplace_back(this);
    else frame_groups.insert({header.GetGroup(), {this}});
}

void basicframe::BasicFrame::Print(std::ofstream& stream) {}
