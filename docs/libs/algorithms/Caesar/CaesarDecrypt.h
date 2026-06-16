#pragma once

#include "Caesar.h"

std::vector<uint8_t> DecryptCaesar(
    const std::vector<uint8_t>& input,
    int shift
);