#include "Rsa.h"
#include "../../helpers/ConvertUtils.h"
#include "../MathCrypto/CryptoUtils.h"

uint64_t EncryptRsaByte(uint64_t messageValue, uint64_t publicKey, uint64_t moduleValue) {
    return modBinary(messageValue, publicKey, moduleValue);
}

vector<uint8_t> EncryptRsa(const vector<uint8_t>& inputBytes, uint64_t publicKey, uint64_t moduleValue) {
    try {
        vector<uint64_t> sourceNumbers = BytesToNumbers(inputBytes);
        vector<uint64_t> encryptedNumbers;
        encryptedNumbers.reserve(sourceNumbers.size());
        for (size_t i = 0; i < sourceNumbers.size(); i++) {
            uint64_t cipherValue = EncryptRsaByte(sourceNumbers[i], publicKey, moduleValue);
            encryptedNumbers.push_back(cipherValue);
        }
        return NumbersToBinary(encryptedNumbers);
    } catch (const exception& exceptionCaught) {
        throw runtime_error(string("Сбой при шифровании RSA: ") + exceptionCaught.what());
    }
}
