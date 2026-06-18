#include "ChaCha20Encrypt.h"
#include <stdexcept>

ByteVec ChaCha20Encrypt(const ByteVec& plaintext, const ByteVec& key, const ByteVec& nonce, uint32_t counter) {
    ChaCha20ValidateRaw(key, nonce);

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