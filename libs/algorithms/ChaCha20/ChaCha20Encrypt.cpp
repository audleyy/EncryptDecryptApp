#include "ChaCha20Encrypt.h"
#include <stdexcept>

using namespace std;

// Прототипы сырых функций без классов, приведенные к CamelCase
void ChaCha20ValidateRaw(const ByteVec& key, const ByteVec& nonce);
void ChaCha20InitContext(uint32_t* state, uint8_t* buffer, size_t* bufferPos, const uint8_t* key, const uint8_t* nonce, uint32_t counter);
void ChaCha20XorRaw(uint32_t* state, uint8_t* buffer, size_t* bufferPos, const uint8_t* input, uint8_t* output, size_t length);
void ChaCha20ClearRaw(uint32_t* state, uint8_t* buffer, size_t* bufferPos);

ByteVec ChaCha20Encrypt(const ByteVec& plaintext, const ByteVec& key, const ByteVec& nonce, uint32_t counter) {
    ChaCha20ValidateRaw(key, nonce);

    // Массивы и переменная позиции в стиле CamelCase
    uint32_t state[16];
    uint8_t buffer[64];
    size_t bufferPos = 64;

    ByteVec ciphertext(plaintext.size());
    try {
        ChaCha20InitContext(state, buffer, &bufferPos, key.data(), nonce.data(), counter);
        ChaCha20XorRaw(state, buffer, &bufferPos, plaintext.data(), ciphertext.data(), plaintext.size());
    } catch (...) {
        ChaCha20ClearRaw(state, buffer, &bufferPos);
        throw;
    }

    ChaCha20ClearRaw(state, buffer, &bufferPos);
    return ciphertext;
}