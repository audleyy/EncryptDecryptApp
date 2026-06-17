#include "KeyFile.h"
#include "../ConvertUtils.h"
#include <fstream>

void SaveKeyNumbersToFile(const string& filePath, const vector<uint64_t>& keyNumbers) {
    vector<uint8_t> keyBytes = NumbersToBinary(keyNumbers);
    ofstream file(filePath, ios::binary);
    if (!file) {
        throw runtime_error("Не удалось открыть файл для записи ключа");
    }
    for (uint8_t byte : keyBytes) {
        file.put(byte);
    }
    if (!file) {
        throw runtime_error("Не удалось записать ключ");
    }
}

vector<uint64_t> ReadKeyNumbersFromFile(const string& filePath) {
    ifstream file(filePath, ios::binary);
    if (!file) {
        throw runtime_error("Не удалось открыть файл для чтения ключа");
    }

    vector<uint8_t> keyBytes;
    char symbol {};
    while (file.get(symbol)) {
        keyBytes.push_back(symbol);
    }
    if (!file.good() && !file.eof()) {
        throw runtime_error("Не удалось прочитать ключ");
    }

    return BinaryToNumbers(keyBytes);
}
