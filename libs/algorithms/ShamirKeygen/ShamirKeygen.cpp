#include "ShamirKeygen.h"
#include "../MathCrypto/CryptoUtils.h"

bool IsShamirSecretKeyValid(int64_t secretKey, int64_t primeValue) {
    bool isValid = true;
    int64_t moduleValue = primeValue - 1;
    if (secretKey <= 1 || secretKey >= moduleValue) {
        isValid = false;
    } else {
        try {
            calculateReverseElement(secretKey, moduleValue);
        } catch (const exception&) {
            isValid = false;
        }
    }
    return isValid;
}

int64_t CalculateShamirReverseKey(int64_t secretKey, int64_t primeValue) {
    try {
        return calculateReverseElement(secretKey, primeValue - 1);
    } catch (const exception& exceptionCaught) {
        throw runtime_error(string("Сбой при вычислении обратного ключа Шамира: ") + exceptionCaught.what());
    }
}

ShamirKey GenerateShamirKey(int64_t primeValue, int64_t caValue, int64_t cbValue) {
    try {
        if (!IsPrime(primeValue)) {
            throw invalid_argument("p должно быть простым числом");
        }
        if (primeValue <= 255) {
            throw invalid_argument("p должно быть больше 255 для шифрования байтов");
        }
        if (!IsShamirSecretKeyValid(caValue, primeValue)) {
            throw invalid_argument("Ca не подходит для выбранного p");
        }
        if (!IsShamirSecretKeyValid(cbValue, primeValue)) {
            throw invalid_argument("Cb не подходит для выбранного p");
        }
        ShamirKey key;
        key.primeValue = primeValue;
        key.caValue = caValue;
        key.cbValue = cbValue;
        key.daValue = CalculateShamirReverseKey(caValue, primeValue);
        key.dbValue = CalculateShamirReverseKey(cbValue, primeValue);
        return key;
    } catch (const exception& exceptionCaught) {
        throw runtime_error(string("Сбой при генерации ключа Шамира: ") + exceptionCaught.what());
    }
}
