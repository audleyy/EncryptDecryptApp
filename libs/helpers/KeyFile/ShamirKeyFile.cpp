#include "KeyFile.h"
#include <vector>

void SaveShamirKeyToFile(const string& filePath, const ShamirKey& key) {
    vector<uint64_t> keyNumbers = {ShamirAlgorithmId, key.primeValue, key.caValue, key.cbValue, key.daValue, key.dbValue};
    SaveKeyNumbersToFile(filePath, keyNumbers);
}

ShamirKey ReadShamirKeyFromFile(const string& filePath) {
    vector<uint64_t> keyNumbers = ReadKeyNumbersFromFile(filePath);
    if (keyNumbers.size() != 6 || keyNumbers[0] != ShamirAlgorithmId) {
        throw runtime_error("Ошибка ключа: файл не является ключом Шамира");
    }
    ShamirKey key;
    key.primeValue = keyNumbers[1];
    key.caValue = keyNumbers[2];
    key.cbValue = keyNumbers[3];
    key.daValue = keyNumbers[4];
    key.dbValue = keyNumbers[5];
    return key;
}
