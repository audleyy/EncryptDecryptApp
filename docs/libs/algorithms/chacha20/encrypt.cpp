#include "ChaCha20.h"
#include <stdexcept>

vector<uint8_t> ChaCha20Encrypt(const vector<uint8_t>& plain, const vector<uint8_t>& key, const vector<uint8_t>& nonce, uint32_t counter) {
    if (key.size() != CHACHA20_KEY_SIZE)
        throw invalid_argument("Ключ должен быть 32 байта");
    if (nonce.size() != CHACHA20_NONCE_SIZE)
        throw invalid_argument("Ключ должен быть 12 байтов");

    ChaCha20Context ctx;
    ChaCha20Init(ctx, key.data(), nonce.data(), counter);
    vector<uint8_t> cipher(plain.size());
    ChaCha20Xor(ctx, plain.data(), cipher.data(), plain.size());
    return cipher;
}