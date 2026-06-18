#include "KeyFile.h"

const uint64_t DhChaCha20AlgorithmId = 6;
const size_t DhChaCha20ParamsFileSize = sizeof(uint64_t) * 5;

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
