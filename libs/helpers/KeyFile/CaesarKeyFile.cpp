#include "KeyFile.h"
#include <vector>

void SaveCaesarKeyToFile(const string& filePath, const CaesarKey& key) {
    vector<uint64_t> keyNumbers = {CaesarAlgorithmId, key.shift};
    SaveKeyNumbersToFile(filePath, keyNumbers);
}

CaesarKey ReadCaesarKeyFromFile(const string& filePath) {
    vector<uint64_t> keyNumbers = ReadKeyNumbersFromFile(filePath);
    if (keyNumbers.size() != 2 || keyNumbers[0] != CaesarAlgorithmId) {
        throw runtime_error("Ошибка ключа: файл не является ключом Caesar");
    }
    return GenerateCaesarKey(keyNumbers[1]);
}
