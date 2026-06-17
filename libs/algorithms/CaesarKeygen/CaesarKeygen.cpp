#include "CaesarKeygen.h"
#include "../MathCrypto/CryptoUtils.h"

using namespace std;

CaesarKey GenerateCaesarKey(uint64_t shift) {
    CaesarKey key;
    key.shift = shift % CaesarAlphabetSize;
    return key;
}

CaesarKey GenerateRandomCaesarKey() {
    uint64_t shift = GenerateRandomUint64(1, CaesarAlphabetSize - 1);
    return GenerateCaesarKey(shift);
}
