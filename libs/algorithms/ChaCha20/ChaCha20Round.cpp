#include "ChaCha20Round.h"

using namespace std;

void QuarterRound(uint32_t& a, uint32_t& b, uint32_t& c, uint32_t& d) {
    a += b; d ^= a; d = Rotl32(d, 16);
    c += d; b ^= c; b = Rotl32(b, 12);
    a += b; d ^= a; d = Rotl32(d, 8);
    c += d; b ^= c; b = Rotl32(b, 7);
}