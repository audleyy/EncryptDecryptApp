#include "ChaCha20.h"

vector<uint8_t> ChaCha20Decrypt(const vector<uint8_t>& cipher, const vector<uint8_t>& key, const vector<uint8_t>& nonce, uint32_t counter) {
    
    return ChaCha20Encrypt(cipher, key, nonce, counter);
}