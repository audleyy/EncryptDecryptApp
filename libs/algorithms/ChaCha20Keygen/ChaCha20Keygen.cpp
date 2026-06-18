#include "ChaCha20Keygen.h"

ChaCha20Key GenerateRandomChaCha20Key() {
    random_device hardwareRandomDevice;
    mt19937 randomEngine(hardwareRandomDevice());
    uniform_int_distribution<int> byteDistribution(0, 255);

    ChaCha20Key key;
    key.key.resize(CHACHA20_KEY_SIZE);
    key.nonce.resize(CHACHA20_NONCE_SIZE);
    key.counter = 0;

    for (size_t index = 0; index < CHACHA20_KEY_SIZE; index++) {
        key.key[index] = byteDistribution(randomEngine);
    }
    for (size_t index = 0; index < CHACHA20_NONCE_SIZE; index++) {
        key.nonce[index] = byteDistribution(randomEngine);
    }

    return key;
}
