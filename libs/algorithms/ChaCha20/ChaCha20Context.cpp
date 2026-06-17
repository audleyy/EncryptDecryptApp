#include "ChaCha20Context.h"
#include "ChaCha20Round.h"
#include <cstring>
#include <stdexcept>
#include <string>

using namespace std;


static const uint32_t SIGMA[4] = {
    0x61707865u, 0x3320646eu,
    0x79622d32u, 0x6b206574u
};

void ChaCha20InitContext(uint32_t* state, uint8_t* buffer, size_t* bufferPos, const uint8_t* key, const uint8_t* nonce, uint32_t counter) {
    memcpy(state, SIGMA, sizeof(SIGMA));

    for (int i = 0; i < 8; i++) {
        state[4 + i] = Load32LE(key + i * 4);
    }
   
    state[12] = counter;
    for (int i = 0; i < 3; i++) {
        state[13 + i] = Load32LE(nonce + i * 4);
    }

    memset(buffer, 0, 64);
    *bufferPos = 64;
}

void ChaCha20NextBlockRaw(uint32_t* state, uint8_t* buffer, size_t* bufferPos) {
  
    if (state[12] == CHACHA20_MAX_COUNTER) {
        throw overflow_error("ChaCha20: переполнение счётчика блоков");
    }

 
    uint32_t working[16];
    memcpy(working, state, sizeof(working));

    for (int round = 0; round < 10; round++) {
        QuarterRound(working[0], working[4], working[8],  working[12]);
        QuarterRound(working[1], working[5], working[9],  working[13]);
        QuarterRound(working[2], working[6], working[10], working[14]);
        QuarterRound(working[3], working[7], working[11], working[15]);
        QuarterRound(working[0], working[5], working[10], working[15]);
        QuarterRound(working[1], working[6], working[11], working[12]);
        QuarterRound(working[2], working[7], working[8],  working[13]);
        QuarterRound(working[3], working[4], working[9],  working[14]);
    }

    for (int i = 0; i < 16; i++) {
        Store32LE(buffer + i * 4, working[i] + state[i]);
    }

    *bufferPos = 0;
  
    state[12]++;
}

void ChaCha20XorRaw(uint32_t* state, uint8_t* buffer, size_t* bufferPos, const uint8_t* input, uint8_t* output, size_t length) {
    for (size_t i = 0; i < length; i++) {
        if (*bufferPos >= 64) {
            ChaCha20NextBlockRaw(state, buffer, bufferPos);
        }
        output[i] = input[i] ^ buffer[(*bufferPos)++];
    }
}

void ChaCha20ClearRaw(uint32_t* state, uint8_t* buffer, size_t* bufferPos) {
    volatile uint8_t* pState = reinterpret_cast<volatile uint8_t*>(state);
    for (size_t i = 0; i < 64; i++) {
        pState[i] = 0;
    }
    volatile uint8_t* pBuf = reinterpret_cast<volatile uint8_t*>(buffer);
    for (size_t i = 0; i < 64; i++) {
        pBuf[i] = 0;
    }
    *bufferPos = 0;
}

void ChaCha20ValidateRaw(const ByteVec& key, const ByteVec& nonce) {
    if (key.size() != CHACHA20_KEY_SIZE) {
        throw invalid_argument("ChaCha20: ключ должен быть 32 байта, получено: " + to_string(key.size()));
    }
    if (nonce.size() != CHACHA20_NONCE_SIZE) {
        throw invalid_argument("ChaCha20: nonce должен быть 12 байт, получено: " + to_string(nonce.size()));
    }
}