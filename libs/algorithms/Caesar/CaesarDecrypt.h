#ifndef CAESAR_DECRYPT_H
#define CAESAR_DECRYPT_H

#include "Caesar.h"
using namespace std;

vector<uint8_t> DecryptCaesar(
    const vector<uint8_t>& input,
    uint64_t shift
);

#endif //