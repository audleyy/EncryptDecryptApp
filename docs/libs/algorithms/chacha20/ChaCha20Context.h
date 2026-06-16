#pragma once

#include "ChaCha20Types.h"

struct ChaCha20Context {
    uint32_t state[16];
    uint8_t  buffer[CHACHA20_BLOCK_SIZE];
    size_t   buffer_pos;

    ChaCha20Context();
    ~ChaCha20Context();

    ChaCha20Context(const ChaCha20Context&)            = delete;
    ChaCha20Context& operator=(const ChaCha20Context&) = delete;
};

void ChaCha20Init(
    ChaCha20Context& ctx,
    const uint8_t*   key,
    const uint8_t*   nonce,
    uint32_t         counter
);

void ChaCha20NextBlock(ChaCha20Context& ctx);

void ChaCha20Xor(
    ChaCha20Context& ctx,
    const uint8_t*   input,
    uint8_t*         output,
    size_t           length
);

void ChaCha20Clear(ChaCha20Context& ctx);

void ChaCha20Validate(
    const ByteVec& key,
    const ByteVec& nonce
);