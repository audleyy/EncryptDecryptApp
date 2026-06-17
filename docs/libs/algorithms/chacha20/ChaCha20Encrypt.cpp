#include "ChaCha20Encrypt.h"
#include <cstring>


void chacha20_init_context(uint32_t* state, uint8_t* buffer, size_t* buffer_pos, const uint8_t* key, const uint8_t* nonce, uint32_t counter);
void chacha20_xor_raw(uint32_t* state, uint8_t* buffer, size_t* buffer_pos, const uint8_t* input, uint8_t* output, size_t length);
void chacha20_clear_raw(uint32_t* state, uint8_t* buffer, size_t* buffer_pos);

ByteVec EncryptChaCha20(const ByteVec& plaintext, const ByteVec& key, const ByteVec& nonce, uint32_t counter) {
    if (key.size() != 32 || nonce.size() != 12) throw std::invalid_argument("ChaCha20: некорректный размер ключа или нонса");
    
    
    uint32_t state[16];
    uint8_t buffer[64];
    size_t buffer_pos = 64;
    
    ByteVec ciphertext(plaintext.size());
    try {
        chacha20_init_context(state, buffer, &buffer_pos, key.data(), nonce.data(), counter);
        chacha20_xor_raw(state, buffer, &buffer_pos, plaintext.data(), ciphertext.data(), plaintext.size());
    } catch (...) {
        chacha20_clear_raw(state, buffer, &buffer_pos);
        throw;
    }
    chacha20_clear_raw(state, buffer, &buffer_pos);
    return ciphertext;
}
