#include "ChaCha20.h"

extern void ChaCha20NextBlock(ChaCha20Context& ctx); // из next_block.cpp

void ChaCha20Xor(ChaCha20Context& ctx, const uint8_t* input, uint8_t* output, size_t length) {
    for (size_t i = 0; i < length; i++) {
        if (ctx.buffer_pos >= CHACHA20_BLOCK_SIZE) {
            ChaCha20NextBlock(ctx);
        }
        output[i] = input[i] ^ ctx.buffer[ctx.buffer_pos++];
    }
}