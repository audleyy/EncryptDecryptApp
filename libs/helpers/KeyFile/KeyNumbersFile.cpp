#include "KeyFile.h"
#include "../BinaryFile.h"
#include "../ConvertUtils.h"

void SaveKeyNumbersToFile(const string& filePath, const vector<uint64_t>& keyNumbers) {
    vector<uint8_t> keyBytes = NumbersToBinary(keyNumbers);
    WriteBinaryFile(filePath, keyBytes);
}

vector<uint64_t> ReadKeyNumbersFromFile(const string& filePath) {
    vector<uint8_t> keyBytes = ReadBinaryFile(filePath);
    try {
        return BinaryToNumbers(keyBytes);
    } catch (const runtime_error& error) {
        throw runtime_error("Ошибка ключа: " + string(error.what()));
    }
}
