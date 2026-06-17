#include "RsaKeygen.h"
#include "../MathCrypto/CryptoUtils.h"

uint64_t CalculateRsaModule(uint64_t pValue, uint64_t qValue) {
    return pValue * qValue;
}

uint64_t CalculateRsaPhi(uint64_t pValue, uint64_t qValue) {
    return (pValue - 1) * (qValue - 1);
}

bool IsRsaPrivateKeyValid(uint64_t privateKey, uint64_t phiValue) {
    bool isValid = true;
    if (privateKey <= 1 || privateKey >= phiValue) {
        isValid = false;
    } else {
        try {
            calculateReverseElement(privateKey, phiValue);
        } catch (const exception&) {
            isValid = false;
        }
    }
    return isValid;
}

uint64_t CalculateRsaPublicKey(uint64_t privateKey, uint64_t phiValue) {
    try {
        return calculateReverseElement(privateKey, phiValue);
    } catch (const exception& exceptionCaught) {
        throw runtime_error(string("Сбой при вычислении открытого ключа RSA: ") + exceptionCaught.what());
    }
}

RsaKey GenerateRsaKey(uint64_t pValue, uint64_t qValue, uint64_t privateKey) {
    try {
        if (!IsPrime(pValue)) {
            throw invalid_argument("p должно быть простым числом");
        }
        if (!IsPrime(qValue)) {
            throw invalid_argument("q должно быть простым числом");
        }
        if (pValue == qValue) {
            throw invalid_argument("p и q должны быть разными простыми числами");
        }
        uint64_t moduleValue = CalculateRsaModule(pValue, qValue);
        if (moduleValue <= 255) {
            throw invalid_argument("n должно быть больше 255 для шифрования байтов");
        }
        uint64_t phiValue = CalculateRsaPhi(pValue, qValue);
        if (!IsRsaPrivateKeyValid(privateKey, phiValue)) {
            throw invalid_argument("секретный ключ не взаимно прост с phi");
        }
        uint64_t publicKey = CalculateRsaPublicKey(privateKey, phiValue);
        RsaKey key;
        key.pValue = pValue;
        key.qValue = qValue;
        key.moduleValue = moduleValue;
        key.phiValue = phiValue;
        key.privateKey = privateKey;
        key.publicKey = publicKey;
        return key;
    } catch (const exception& exceptionCaught) {
        throw runtime_error(string("Сбой при генерации ключа RSA: ") + exceptionCaught.what());
    }
}
