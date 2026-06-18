#include "Shamir.h"

uint64_t CalculateShamirX3(uint64_t x2Value, uint64_t daValue, uint64_t primeValue) {
    return modBinary(x2Value, daValue, primeValue);
}

uint64_t CalculateShamirX4(uint64_t x3Value, uint64_t dbValue, uint64_t primeValue) {
    return modBinary(x3Value, dbValue, primeValue);
}

vector<uint8_t> DecryptShamir(const vector<uint8_t>& inputBytes, uint64_t primeValue, uint64_t daValue, uint64_t dbValue) {
    try {
        vector<uint64_t> encryptedNumbers = BinaryToNumbers(inputBytes);
        vector<uint64_t> decryptedNumbers;
        decryptedNumbers.reserve(encryptedNumbers.size());
        for (size_t i = 0; i < encryptedNumbers.size(); i++) {
            uint64_t x3Value = CalculateShamirX3(encryptedNumbers[i], daValue, primeValue);
            uint64_t x4Value = CalculateShamirX4(x3Value, dbValue, primeValue);
            decryptedNumbers.push_back(x4Value);
        }

        return NumbersToBytes(decryptedNumbers);
    } catch (const exception& exceptionCaught) {
        throw runtime_error(string("Сбой при дешифровании Шамира: ") + exceptionCaught.what());
    }
}
