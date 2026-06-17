#include "ChaCha20Core.h"
#include <cstring>
#include <exception>

using namespace std;

static const uint32_t SIGMA[4] = {0x61707865u, 0x3320646eu, 0x79622d32u, 0x6b206574u};


void chacha20_init_context(uint32_t* state, uint8_t* buffer, size_t* buffer_pos, const uint8_t* key, const uint8_t* nonce, uint32_t counter) {
    memcpy(state, SIGMA, sizeof(SIGMA));
    for (int i = 0; i < 8; i++) state[4 + i] = load32LE(key + i * 4);
    state[12] = counter;
    for (int i = 0; i < 3; i++) state[13 + i] = load32LE(nonce + i * 4);
    memset(buffer, 0, 64);
    *buffer_pos = 64;
}


void chacha20_next_block_raw(uint32_t* state, uint8_t* buffer, size_t* buffer_pos) {
    if (state[12] == 0xFFFFFFFFu) throw overflow_error("ChaCha20: переполнение счётчика блоков");
    uint32_t working[16];
    memcpy(working, state, sizeof(working));
    for (int round = 0; round < 10; round++) {
        quarterRound(working[0], working[4], working[8],  working[12]);
        quarterRound(working[1], working[5], working[9],  working[13]);
        quarterRound(working[2], working[6], working[10], working[14]);
        quarterRound(working[3], working[7], working[11], working[15]);
        quarterRound(working[0], working[5], working[10], working[15]);
        quarterRound(working[1], working[6], working[11], working[12]);
        quarterRound(working[2], working[7], working[8],  working[13]);
        quarterRound(working[3], working[4], working[9],  working[14]);
    }
    for (int i = 0; i < 16; i++) store32LE(buffer + i * 4, working[i] + state[i]);
    *buffer_pos = 0;
    state[12]++;
}


void chacha20_xor_raw(uint32_t* state, uint8_t* buffer, size_t* buffer_pos, const uint8_t* input, uint8_t* output, size_t length) {
    for (size_t i = 0; i < length; i++) {
        if (*buffer_pos >= 64) chacha20_next_block_raw(state, buffer, buffer_pos);
        output[i] = input[i] ^ buffer[(*buffer_pos)++];
    }
}


void chacha20_clear_raw(uint32_t* state, uint8_t* buffer, size_t* buffer_pos) {
    volatile uint8_t* p_state = reinterpret_cast<volatile uint8_t*>(state);
    for (size_t i = 0; i < 64; i++) p_state[i] = 0;
    volatile uint8_t* p_buf = reinterpret_cast<volatile uint8_t*>(buffer);
    for (size_t i = 0; i < 64; i++) p_buf[i] = 0;
    *buffer_pos = 0;
}
