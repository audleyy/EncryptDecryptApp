#pragma once

#include "Caesar.h"

std::vector<uint8_t> EncryptCaesar(
    const std::vector<uint8_t>& input,
    int shift
);
