#include "KeyFile.h"
#include <vector>

void SaveRsaKeyToFile(const string& filePath, const RsaKey& key) {
    vector<uint64_t> keyNumbers = {RsaAlgorithmId, key.moduleValue, key.publicKey, key.privateKey};
    SaveKeyNumbersToFile(filePath, keyNumbers);
}

RsaKey ReadRsaKeyFromFile(const string& filePath) {
    vector<uint64_t> keyNumbers = ReadKeyNumbersFromFile(filePath);
    if (keyNumbers.size() != 4 || keyNumbers[0] != RsaAlgorithmId) {
        throw runtime_error("Ошибка ключа: файл не является RSA-ключом");
    }
    RsaKey key;
    key.pValue = 0;
    key.qValue = 0;
    key.phiValue = 0;
    key.moduleValue = keyNumbers[1];
    key.publicKey = keyNumbers[2];
    key.privateKey = keyNumbers[3];
    return key;
}
