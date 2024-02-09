#include "includes.h"


uint32_t ToSyncSafeInteger(const char* bytes) {
    uint32_t number = 0;
    for (int i = 0; i < 4; i++) {
        number += *(bytes + i);
        if (i != 3) number <<= 7;
    }

    return number;
}

void TrimString(std::string& str) {
    while (!str.empty() && str.back() == '\0') {
        str.pop_back();
    }
}
