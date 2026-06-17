#include "ChaCha20Keygen.h"
#include <random>

using namespace std;

ChaCha20Key ChaCha20GenerateKey() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 255);

    ChaCha20Key result;
    result.key.resize(CHACHA20_KEY_SIZE);
    result.nonce.resize(CHACHA20_NONCE_SIZE);

    for (size_t i = 0; i < CHACHA20_KEY_SIZE; i++) {
        result.key[i] = (uint8_t)dist(gen);
    }
    for (size_t i = 0; i < CHACHA20_NONCE_SIZE; i++) {
        result.nonce[i] = (uint8_t)dist(gen);
    }

    return result;
}
