#include "KeyFile.h"
#include "../BinaryFile.h"
#include "../ConvertUtils.h"

const size_t ChaCha20HeaderSize = sizeof(uint64_t) * 2;
const size_t ChaCha20KeyFileSize = ChaCha20HeaderSize + CHACHA20_KEY_SIZE + CHACHA20_NONCE_SIZE;

void SaveChaCha20KeyToFile(const string& filePath, const ChaCha20Key& key) {
    if (key.key.size() != CHACHA20_KEY_SIZE || key.nonce.size() != CHACHA20_NONCE_SIZE) {
        throw runtime_error("Ошибка ключа: некорректный размер ключа ChaCha20");
    }
    vector<uint64_t> headerNumbers = {ChaCha20AlgorithmId, key.counter};
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
    if (headerNumbers.size() != 2 || headerNumbers[0] != ChaCha20AlgorithmId) {
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
