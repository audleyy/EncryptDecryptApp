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

// Генерирует ChaCha20Key из общего секрета Diffie-Hellman.
// Схема:
//   pubA = g^privA mod p
//   pubB = g^privB mod p
//   sharedSecret = pubB^privA mod p  (= pubA^privB mod p)
// Из sharedSecret заполняем key (32 байта) и nonce (12 байта)
// через побайтное разложение с ротацией.
ChaCha20Key GenerateChaCha20KeyFromDH(const DhChaCha20Params& params) {
    // Вычисляем публичные ключи сторон
    uint64_t pubA = GeneratePublicKey(params.generator, params.privateKeyA, params.primeModulus);
    uint64_t pubB = GeneratePublicKey(params.generator, params.privateKeyB, params.primeModulus);

    // Вычисляем общий секрет (обе стороны получат одинаковый результат)
    uint64_t sharedSecret = GenerateSharedSecret(pubB, params.privateKeyA, params.primeModulus);

    // Проверка корректности: sharedSecret должен совпасть с обеих сторон
    uint64_t sharedSecretCheck = GenerateSharedSecret(pubA, params.privateKeyB, params.primeModulus);
    if (sharedSecret != sharedSecretCheck) {
        throw runtime_error("Ошибка ключа: общий секрет Diffie-Hellman не совпал");
    }

    // Разворачиваем 64-битный sharedSecret в (32 + 12) = 44 байта
    // путём ротации байт секрета по кругу
    ChaCha20Key key;
    key.key.resize(CHACHA20_KEY_SIZE);
    key.nonce.resize(CHACHA20_NONCE_SIZE);
    key.counter = 0;

    // Раскладываем sharedSecret в массив из 8 байт
    uint8_t secretBytes[8];
    for (int i = 0; i < 8; i++) {
        secretBytes[i] = static_cast<uint8_t>((sharedSecret >> (i * 8)) & 0xFF);
    }

    // Заполняем key[32]: каждый байт = secretBytes[i % 8] XOR i
    for (size_t i = 0; i < CHACHA20_KEY_SIZE; i++) {
        key.key[i] = secretBytes[i % 8] ^ static_cast<uint8_t>(i);
    }

    // Заполняем nonce[12]: каждый байт = secretBytes[(i+1) % 8] XOR (i + 32)
    for (size_t i = 0; i < CHACHA20_NONCE_SIZE; i++) {
        key.nonce[i] = secretBytes[(i + 1) % 8] ^ static_cast<uint8_t>(i + CHACHA20_KEY_SIZE);
    }

    return key;
}