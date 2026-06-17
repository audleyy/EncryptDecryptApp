#include "Rsa.h"
#include "../../helpers/ConvertUtils.h"
#include "../MathCrypto/CryptoUtils.h"

uint64_t DecryptRsaByte(uint64_t cipherValue, uint64_t privateKey, uint64_t moduleValue) {
    return modBinary(cipherValue, privateKey, moduleValue);
}

vector<uint8_t> DecryptRsa(const vector<uint8_t>& inputBytes, uint64_t privateKey, uint64_t moduleValue) {
    try {
        vector<uint64_t> encryptedNumbers = BinaryToNumbers(inputBytes);
        vector<uint64_t> decryptedNumbers;
        decryptedNumbers.reserve(encryptedNumbers.size());
        for (size_t i = 0; i < encryptedNumbers.size(); i++) {
            uint64_t byteValue = DecryptRsaByte(encryptedNumbers[i], privateKey, moduleValue);
            decryptedNumbers.push_back(byteValue);
        }
        return NumbersToBytes(decryptedNumbers);
    } catch (const exception& exceptionCaught) {
        throw runtime_error(string("Сбой при дешифровании RSA: ") + exceptionCaught.what());
    }
}
