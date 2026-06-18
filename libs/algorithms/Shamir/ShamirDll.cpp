#include "Shamir.h"

extern "C" int encrypt(const uint8_t* inputData, size_t inputSize, uint64_t primeValue, uint64_t caValue, uint64_t cbValue, uint8_t* outputData, size_t outputCapacity, size_t* outputSize) {
    try {
        if (outputSize == nullptr || (inputData == nullptr && inputSize > 0)) {
            throw invalid_argument("Некорректные входные данные Shamir encrypt");
        } 
        vector<uint8_t> inputBytes(inputData, inputData + inputSize);
        vector<uint8_t> resultBytes = EncryptShamir(inputBytes, primeValue, caValue, cbValue);
        *outputSize = resultBytes.size();
        if (outputData == nullptr || outputCapacity < resultBytes.size()) {
            throw length_error("Недостаточный размер выходного буфера Shamir encrypt");
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

extern "C" int decrypt(const uint8_t* inputData, size_t inputSize, uint64_t primeValue, uint64_t daValue, uint64_t dbValue, uint8_t* outputData, size_t outputCapacity, size_t* outputSize) {
    try {
        if (outputSize == nullptr || (inputData == nullptr && inputSize > 0)) {
            throw invalid_argument("Некорректные входные данные Shamir decrypt");
        } 
        vector<uint8_t> inputBytes(inputData, inputData + inputSize);
        vector<uint8_t> resultBytes = DecryptShamir(inputBytes, primeValue, daValue, dbValue);
        *outputSize = resultBytes.size(); 
        if (outputData == nullptr || outputCapacity < resultBytes.size()) {
            throw length_error("Недостаточный размер выходного буфера Shamir decrypt");
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
