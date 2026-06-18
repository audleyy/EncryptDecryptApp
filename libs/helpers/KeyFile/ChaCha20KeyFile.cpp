#include "KeyFile.h"

const size_t ChaCha20HeaderSize = sizeof(uint64_t) * 2;
const size_t ChaCha20KeyFileSize = ChaCha20HeaderSize + CHACHA20_KEY_SIZE + CHACHA20_NONCE_SIZE;
const uint64_t DhChaCha20AlgorithmId = 6;
const size_t DhChaCha20ParamsFileSize = sizeof(uint64_t) * 5;

void SaveChaCha20KeyToFile(const string& filePath, const ChaCha20Key& key) {
    if (key.key.size() != CHACHA20_KEY_SIZE || key.nonce.size() != CHACHA20_NONCE_SIZE) {
        throw runtime_error("Ошибка ключа: некорректный размер ключа ChaCha20");
    }
    vector<uint64_t> headerNumbers = {CaesarAlgorithmId + 1, key.counter}; // Равно 5 (ChaCha20AlgorithmId из .h)
    vector<uint8_t> keyBytes = NumbersToBinary(headerNumbers);
    keyBytes.insert(keyBytes.end(), key.key.begin(), key.key.end());
    keyBytes.insert(keyBytes.end(), key.nonce.begin(), key.nonce.end());
    WriteBinaryFile(filePath, keyBytes);
}

ChaCha20Key ReadChaCha20KeyFromFile(const string& filePath) {
    vector<uint8_t> keyBytes = ReadBinaryFile(filePath);
    if (keyBytes.size() != ChaCha20KeyFileSize) {
        throw runtime_error("Ошибка ключа: файл не является ключом ChaCha20");
    }
    vector<uint8_t> headerBytes(keyBytes.begin(), keyBytes.begin() + ChaCha20HeaderSize);
    vector<uint64_t> headerNumbers = BinaryToNumbers(headerBytes);
    if (headerNumbers.size() != 2 || headerNumbers[0] != (CaesarAlgorithmId + 1)) {
        throw runtime_error("Ошибка ключа: файл не является ключом ChaCha20");
    }
    if (headerNumbers[1] > CHACHA20_MAX_COUNTER) {
        throw runtime_error("Ошибка ключа: некорректный счетчик ChaCha20");
    }
    ChaCha20Key key;
    key.counter = headerNumbers[1];
    key.key.assign(keyBytes.begin() + ChaCha20HeaderSize, keyBytes.begin() + ChaCha20HeaderSize + CHACHA20_KEY_SIZE);
    key.nonce.assign(keyBytes.begin() + ChaCha20HeaderSize + CHACHA20_KEY_SIZE, keyBytes.end());
    return key;
}

void SaveDhChaCha20ParamsToFile(const string& filePath, const DhChaCha20Params& params) {
    vector<uint64_t> numbers = {
        DhChaCha20AlgorithmId,
        params.primeModulus,
        params.generator,
        params.privateKeyA,
        params.privateKeyB
    };
    vector<uint8_t> bytes = NumbersToBinary(numbers);
    WriteBinaryFile(filePath, bytes);
}

DhChaCha20Params ReadDhChaCha20ParamsFromFile(const string& filePath) {
    vector<uint8_t> bytes = ReadBinaryFile(filePath);
    if (bytes.size() != DhChaCha20ParamsFileSize) {
        throw runtime_error("Ошибка ключа: файл не является DH-параметрами ChaCha20");
    }
    vector<uint64_t> numbers = BinaryToNumbers(bytes);
    if (numbers[0] != DhChaCha20AlgorithmId) {
        throw runtime_error("Ошибка ключа: файл не является DH-параметрами ChaCha20");
    }
    DhChaCha20Params params;
    params.primeModulus = numbers[1];
    params.generator    = numbers[2];
    params.privateKeyA  = numbers[3];
    params.privateKeyB  = numbers[4];
    return params;
}
