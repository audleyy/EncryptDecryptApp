#include "ChaCha20.h"
#include <cstring>

extern void quarterRound(uint32_t&, uint32_t&, uint32_t&, uint32_t&);

static void ChaCha20NextBlock(ChaCha20Context& ctx) {
    uint32_t working[16];
    memcpy(working, ctx.state, 64);
    for (int round = 0; round < 10; round++) {
        quarterRound(working[0], working[4], working[8], working[12]);
        quarterRound(working[1], working[5], working[9], working[13]);
        quarterRound(working[2], working[6], working[10], working[14]);
        quarterRound(working[3], working[7], working[11], working[15]);
        quarterRound(working[0], working[5], working[10], working[15]);
        quarterRound(working[1], working[6], working[11], working[12]);
        quarterRound(working[2], working[7], working[8], working[13]);
        quarterRound(working[3], working[4], working[9], working[14]);
    }
    for (int i = 0; i < 16; i++) {
        uint32_t x = working[i] + ctx.state[i];
        ctx.buffer[i*4]   = (x >> 0) & 0xFF;
        ctx.buffer[i*4+1] = (x >> 8) & 0xFF;
        ctx.buffer[i*4+2] = (x >> 16) & 0xFF;
        ctx.buffer[i*4+3] = (x >> 24) & 0xFF;
    }
    ctx.buffer_pos = 0;
    ctx.state[12]++;
}