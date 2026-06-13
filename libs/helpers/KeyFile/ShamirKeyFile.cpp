#include "KeyFile.h"
#include "../ConvertUtils.h"
#include <fstream>
#include <vector>

void SaveShamirKeyToFile(const string& filePath, const ShamirKey& key) {
    vector<int64_t> keyNumbers = { key.primeValue, key.caValue, key.cbValue, key.daValue, key.dbValue, };
    vector<uint8_t> keyBytes = NumbersToBinary(keyNumbers);
    ofstream file(filePath, ios::binary);
    if (!file) {
        throw runtime_error("Не удалось открыть файл для записи ключа Шамира");
    }
    file.write(reinterpret_cast<const char*>(keyBytes.data()), keyBytes.size());
}

ShamirKey ReadShamirKeyFromFile(const string& filePath) {
    ifstream file(filePath, ios::binary);
    if (!file) {
        throw runtime_error("Не удалось открыть файл для чтения ключа Шамира");
    }
    vector<uint8_t> keyBytes((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    vector<int64_t> keyNumbers = BinaryToNumbers(keyBytes);
    if (keyNumbers.size() != 5) {
        throw runtime_error("Некорректный размер файла ключа Шамира");
    }
    ShamirKey key;
    key.primeValue = keyNumbers[0];
    key.caValue = keyNumbers[1];
    key.cbValue = keyNumbers[2];
    key.daValue = keyNumbers[3];
    key.dbValue = keyNumbers[4];
    return key;
}
