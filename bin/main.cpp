#include "lib\ID3v2HeadFooter.h"
#include "lib\UFIDnPRIVFrame.h"
#include "lib\TextFrame.h"
#include "lib\TextCommentFrame.h"
#include "lib\POPMFrame.h"
#include "lib\WebFrame.h"
#include "lib\SkippedFrame.h"
#include "lib\UserTextFrame.h"
#include "lib\ETCOFrame.h"
#include "lib\SYLTFrame.h"
#include "lib\RVA2Frame.h"
#include "lib\EQU2Frame.h"
#include "lib\PCNTFrame.h"
#include "lib\POSSFrame.h"
#include "lib\USERFrame.h"
#include "lib\OWNEFrame.h"
#include "lib\GRIDFrame.h"
#include "lib\TIPLnTMCLFrame.h"
#include "lib\SEEKFrame.h"
#include "lib\ENCRFrame.h"
#include "lib\RBUFFrame.h"
#include "lib\COMRFrame.h"
#include <iostream>


int main([[maybe_unused]] int argc, char** argv) {
    try {
        std::ifstream file = std::ifstream(argv[1], std::ios_base::binary | std::ios_base::in);
        if (!file.is_open()) throw std::runtime_error("File is not available");

        id3headfooter::HeadFooter file_header(file);
        if (file_header.ExtendedHeaderEnabled()) {}

        uint32_t bytes_read = 0;
        while (bytes_read < file_header.GetSize()) {
            char data[4];
            file.read(&data[0], 4);
            switch (data[0]) {
                case 'U':
                    if (strncmp(data, "UFID", 4) == 0)
                        new ufidframe::UFIDnPRIVFrame{const_cast<char*>("UFID"), file, bytes_read};
                    if (strncmp(data, "USER", 4) == 0)
                        new userframe::USERFrame{file, bytes_read};
                    else
                        new tcframe::TCFrame{data, file, bytes_read};
                    break;
                case 'T':
                    if (strncmp(data, "TXXX", 4) == 0)
                        new usertextframe::UTFrame{data, file, bytes_read};
                    else if (strncmp(data, "TIPL", 4) == 0 || strncmp(data, "TMCL", 4) == 0)
                        new tiplntmclframe::TIPLnTMCLFrame{data, file, bytes_read};
                    else
                        new textframe::TFrame{data, file, bytes_read};
                    break;
                case 'C':
                    if (strncmp(data, "COMR", 4) == 0)
                        new comrframe::COMRFrame{file, bytes_read};
                    else
                        new tcframe::TCFrame{data, file, bytes_read};
                    break;
                case 'P':
                    if (strncmp(data, "PCNT", 4) == 0)
                        new pcntframe::PCNTFrame{file, bytes_read};
                    else if (strncmp(data, "POPM", 4) == 0)
                        new popmframe::POPMFrame{file, bytes_read};
                    else if (strncmp(data, "PRIV", 4) == 0)
                        new ufidframe::UFIDnPRIVFrame{const_cast<char*>("PRIV"), file, bytes_read};
                    else
                        new possframe::POSSFrame{file, bytes_read};
                    break;
                case 'W':
                    if (strncmp(data, "WXXX", 4) == 0)
                        new usertextframe::UTFrame{data, file, bytes_read};
                    else
                        new webframe::WebFrame{data, file, bytes_read};
                    break;
                case 'E':
                    if (strncmp(data, "ETCO", 4) == 0)
                        new etcoframe::ETCOFrame{file, bytes_read};
                    else if (strncmp(data, "ENCR", 4) == 0)
                        new encrframe::ENCRFrame{file, bytes_read};
                    else
                        new equ2frame::EQU2Frame{file, bytes_read};
                    break;
                case 'S':
                    if (strncmp(data, "SYLT", 4) == 0)
                        new syltframe::SYLTFrame{file, bytes_read};
                    else
                        new seekframe::SEEKFrame{file, bytes_read};
                    break;
                case 'R':
                    if (strncmp(data, "RVA2", 4) == 0)
                        new rva2frame::RVA2Frame{file, bytes_read};
                    else
                        new rbufframe::RBUFFrame{file, bytes_read};
                    break;
                case 'O':
                    new owneframe::OWNEFrame{file, bytes_read};
                    break;
                case 'G':
                    new gridframe::GRIDFrame{file, bytes_read};
                    break;
                default:
                    if (data[0] == '\0') goto after_padding;
                    new skippedframe::SkippedFrame{data, file, bytes_read};
            }
        }
        after_padding:
        std::ofstream output{"out.txt"};
        for (auto& group: frame_groups) {
            output << "Group ";
            if (group.first) output << group.first << " :\n";
            else output << "default:\n";
            for (auto frame: group.second) {
                frame->Print(output);
            }
        }
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << '\n';
    }
}
