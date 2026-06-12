#include "Rsa.h"
#include "../../helpers/ConvertUtils.h"
#include "../MathCrypto/CryptoUtils.h"

int64_t EncryptRsaByte(int64_t messageValue, int64_t publicKey, int64_t moduleValue) {
    return modBinary(messageValue, publicKey, moduleValue);
}

vector<uint8_t> EncryptRsa(const vector<uint8_t>& inputBytes, int64_t publicKey, int64_t moduleValue) {
    try {
        vector<int64_t> sourceNumbers = BytesToNumbers(inputBytes);
        vector<int64_t> encryptedNumbers;
        encryptedNumbers.reserve(sourceNumbers.size());
        for (size_t i = 0; i < sourceNumbers.size(); i++) {
            int64_t cipherValue = EncryptRsaByte(sourceNumbers[i], publicKey, moduleValue);
            encryptedNumbers.push_back(cipherValue);
        }
        return NumbersToBinary(encryptedNumbers);
    } catch (const exception& exceptionCaught) {
        throw runtime_error(string("Сбой при шифровании RSA: ") + exceptionCaught.what());
    }
}
