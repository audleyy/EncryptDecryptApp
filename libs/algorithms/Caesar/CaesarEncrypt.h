#pragma once

#include "Caesar.h"

using namespace std;

vector<uint8_t> EncryptCaesar(
    const std::vector<uint8_t>& input,
    uint64_t shift
);
