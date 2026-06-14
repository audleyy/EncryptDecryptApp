#include "ChaCha20.h"
#include <cstring>

extern void quarterRound(uint32_t&, uint32_t&, uint32_t&, uint32_t&); // объявление из utils.cpp

void ChaCha20Init(ChaCha20Context& ctx, const uint8_t* key, const uint8_t* nonce, uint32_t counter) {
    const uint32_t constants[4] = {0x61707865, 0x3320646e, 0x79622d32, 0x6b206574};
    memcpy(ctx.state, constants, 16);
    for (int i = 0; i < 8; i++) {
        ctx.state[4 + i] = ((uint32_t)key[i*4]) |
                           ((uint32_t)key[i*4+1] << 8) |
                           ((uint32_t)key[i*4+2] << 16) |
                           ((uint32_t)key[i*4+3] << 24);
    }
    ctx.state[12] = counter;
    for (int i = 0; i < 3; i++) {
        ctx.state[13 + i] = ((uint32_t)nonce[i*4]) |
                            ((uint32_t)nonce[i*4+1] << 8) |
                            ((uint32_t)nonce[i*4+2] << 16) |
                            ((uint32_t)nonce[i*4+3] << 24);
    }
    ctx.buffer_pos = CHACHA20_BLOCK_SIZE;
}