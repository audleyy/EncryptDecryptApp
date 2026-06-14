#ifndef CHACHA20_H
#define CHACHA20_H

#include <cstdint>
#include <vector>

using namespace std;

#define CHACHA20_KEY_SIZE   32
#define CHACHA20_NONCE_SIZE 12
#define CHACHA20_BLOCK_SIZE 64

struct ChaCha20Context {
    uint32_t state[16];
    uint8_t buffer[CHACHA20_BLOCK_SIZE];
    uint32_t buffer_pos;
};


void ChaCha20Init(ChaCha20Context& ctx, const uint8_t* key, const uint8_t* nonce, uint32_t counter);
void ChaCha20Xor(ChaCha20Context& ctx, const uint8_t* input, uint8_t* output, size_t length);


vector<uint8_t> ChaCha20Encrypt(const vector<uint8_t>& plain, const vector<uint8_t>& key, const vector<uint8_t>& nonce, uint32_t counter = 0);
vector<uint8_t> ChaCha20Decrypt(const vector<uint8_t>& cipher, const vector<uint8_t>& key, const vector<uint8_t>& nonce, uint32_t counter = 0);

#endif