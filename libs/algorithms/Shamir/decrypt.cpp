#include "Shamir.h"
#include "../../helpers/ConvertUtils.h"
#include "../MathCrypto/CryptoUtils.h"

int64_t CalculateShamirX3(int64_t x2Value, int64_t daValue, int64_t primeValue) {
    return modBinary(x2Value, daValue, primeValue);
}

int64_t CalculateShamirX4(int64_t x3Value, int64_t dbValue, int64_t primeValue) {
    return modBinary(x3Value, dbValue, primeValue);
}

vector<uint8_t> DecryptShamir(const vector<uint8_t>& inputBytes, int64_t primeValue, int64_t daValue, int64_t dbValue) {
    try {
        vector<int64_t> encryptedNumbers = BinaryToNumbers(inputBytes);
        vector<int64_t> decryptedNumbers;
        decryptedNumbers.reserve(encryptedNumbers.size());
        for (size_t i = 0; i < encryptedNumbers.size(); i++) {
            int64_t x3Value = CalculateShamirX3(encryptedNumbers[i], daValue, primeValue);
            int64_t x4Value = CalculateShamirX4(x3Value, dbValue, primeValue);
            decryptedNumbers.push_back(x4Value);
        }

        return NumbersToBytes(decryptedNumbers);
    } catch (const exception& exceptionCaught) {
        throw runtime_error(string("Сбой при дешифровании Шамира: ") + exceptionCaught.what());
    }
}
