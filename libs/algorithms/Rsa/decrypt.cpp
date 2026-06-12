#include "Rsa.h"
#include "../../helpers/ConvertUtils.h"
#include "../MathCrypto/CryptoUtils.h"

int64_t DecryptRsaByte(int64_t cipherValue, int64_t privateKey, int64_t moduleValue) {
    return modBinary(cipherValue, privateKey, moduleValue);
}

vector<uint8_t> DecryptRsa(const vector<uint8_t>& inputBytes, int64_t privateKey, int64_t moduleValue) {
    try {
        vector<int64_t> encryptedNumbers = BinaryToNumbers(inputBytes);
        vector<int64_t> decryptedNumbers;
        decryptedNumbers.reserve(encryptedNumbers.size());
        for (size_t i = 0; i < encryptedNumbers.size(); i++) {
            int64_t byteValue = DecryptRsaByte(encryptedNumbers[i], privateKey, moduleValue);
            decryptedNumbers.push_back(byteValue);
        }
        return NumbersToBytes(decryptedNumbers);
    } catch (const exception& exceptionCaught) {
        throw runtime_error(string("Сбой при дешифровании RSA: ") + exceptionCaught.what());
    }
}
