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


ChaCha20Key GenerateChaCha20KeyFromDH(const DhChaCha20Params& params) {
    
    uint64_t pubA = GeneratePublicKey(params.generator, params.privateKeyA, params.primeModulus);
    uint64_t pubB = GeneratePublicKey(params.generator, params.privateKeyB, params.primeModulus);

  
    uint64_t sharedSecret = GenerateSharedSecret(pubB, params.privateKeyA, params.primeModulus);

   
    uint64_t sharedSecretCheck = GenerateSharedSecret(pubA, params.privateKeyB, params.primeModulus);
    if (sharedSecret != sharedSecretCheck) {
        throw runtime_error("Ошибка ключа: общий секрет Diffie-Hellman не совпал");
    }

   
    ChaCha20Key key;
    key.key.resize(CHACHA20_KEY_SIZE);
    key.nonce.resize(CHACHA20_NONCE_SIZE);
    key.counter = 0;

    
    uint8_t secretBytes[8];
    for (int i = 0; i < 8; i++) {
        secretBytes[i] = static_cast<uint8_t>((sharedSecret >> (i * 8)) & 0xFF);
    }

  
    for (size_t i = 0; i < CHACHA20_KEY_SIZE; i++) {
        key.key[i] = secretBytes[i % 8] ^ static_cast<uint8_t>(i);
    }


    for (size_t i = 0; i < CHACHA20_NONCE_SIZE; i++) {
        key.nonce[i] = secretBytes[(i + 1) % 8] ^ static_cast<uint8_t>(i + CHACHA20_KEY_SIZE);
    }

    return key;
}