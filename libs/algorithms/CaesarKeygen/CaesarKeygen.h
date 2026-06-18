#pragma once

#include "../Caesar/Caesar.h"
#include "../MathCrypto/CryptoUtils.h"

CaesarKey GenerateCaesarKey(uint64_t shift);
CaesarKey GenerateRandomCaesarKey();
