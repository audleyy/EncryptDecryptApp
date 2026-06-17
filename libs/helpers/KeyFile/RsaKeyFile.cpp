#include "KeyFile.h"
#include "../ConvertUtils.h"
#include <fstream>
#include <vector>

void SaveRsaKeyToFile(const string& filePath, const RsaKey& key) {
    vector<int64_t> keyNumbers = { key.moduleValue, key.publicKey, key.privateKey,
    };
    vector<uint8_t> keyBytes = NumbersToBinary(keyNumbers);
    ofstream file(filePath, ios::binary);
    if (!file) {
        throw runtime_error("Не удалось открыть файл для записи RSA-ключа");
    }
    file.write(reinterpret_cast<const char*>(keyBytes.data()), keyBytes.size());
}

RsaKey ReadRsaKeyFromFile(const string& filePath) {
    ifstream file(filePath, ios::binary);
    if (!file) {
        throw runtime_error("Не удалось открыть файл для чтения RSA-ключа");
    }
    vector<uint8_t> keyBytes((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    vector<int64_t> keyNumbers = BinaryToNumbers(keyBytes);
    if (keyNumbers.size() != 3) {
        throw runtime_error("Некорректный размер файла RSA-ключа");
    }
    RsaKey key;
    key.pValue = 0;
    key.qValue = 0;
    key.phiValue = 0;
    key.moduleValue = keyNumbers[0];
    key.publicKey = keyNumbers[1];
    key.privateKey = keyNumbers[2];
    return key;
}
