#include "Rsa.h"

extern "C" int encrypt(const uint8_t* inputData, size_t inputSize, uint64_t publicKey, uint64_t moduleValue, uint8_t* outputData, size_t outputCapacity, size_t* outputSize) {
    try {
        if (outputSize == nullptr || (inputData == nullptr && inputSize > 0)) {
            throw invalid_argument("Некорректные входные данные RSA encrypt");
        }
        vector<uint8_t> inputBytes(inputData, inputData + inputSize);
        vector<uint8_t> resultBytes = EncryptRsa(inputBytes, publicKey, moduleValue);
        *outputSize = resultBytes.size();
        if (outputData == nullptr || outputCapacity < resultBytes.size()) {
            throw length_error("Недостаточный размер выходного буфера RSA encrypt");
        }
        copy(resultBytes.begin(), resultBytes.end(), outputData);
        return 0;
    } catch (const invalid_argument&) {
        return 1;
    } catch (const length_error&) {
        return 2;
    } catch (const exception&) {
        return 3;
    }
}
extern "C" int decrypt(const uint8_t* inputData, size_t inputSize, uint64_t privateKey, uint64_t moduleValue, uint8_t* outputData, size_t outputCapacity, size_t* outputSize) {
    try {
        if (outputSize == nullptr || (inputData == nullptr && inputSize > 0)) {
            throw invalid_argument("Некорректные входные данные RSA decrypt");
        }
        vector<uint8_t> inputBytes(inputData, inputData + inputSize);
        vector<uint8_t> resultBytes = DecryptRsa(inputBytes, privateKey, moduleValue);
        *outputSize = resultBytes.size();
        if (outputData == nullptr || outputCapacity < resultBytes.size()) {
            throw length_error("Недостаточный размер выходного буфера RSA decrypt");
        }
        copy(resultBytes.begin(), resultBytes.end(), outputData);
        return 0;
    } catch (const invalid_argument&) {
        return 1;
    } catch (const length_error&) {
        return 2;
    } catch (const exception&) {
        return 3;
    }
}
