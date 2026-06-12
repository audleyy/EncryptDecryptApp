#ifndef RSA_KEYGEN_H
#define RSA_KEYGEN_H

#include <cstdint>
#include <stdexcept>
#include <string>

using namespace std;

struct RsaKey {
    int64_t pValue;
    int64_t qValue;
    int64_t moduleValue;
    int64_t phiValue;
    int64_t privateKey;
    int64_t publicKey;
};

int64_t CalculateRsaModule(int64_t pValue, int64_t qValue);
int64_t CalculateRsaPhi(int64_t pValue, int64_t qValue);
bool IsRsaPrivateKeyValid(int64_t privateKey, int64_t phiValue);
int64_t CalculateRsaPublicKey(int64_t privateKey, int64_t phiValue);
RsaKey GenerateRsaKey(int64_t pValue, int64_t qValue, int64_t privateKey);
int64_t GenerateRandomPrime(int64_t minValue, int64_t maxValue);
int64_t GenerateRandomRsaPrivateKey(int64_t phiValue);
RsaKey GenerateRandomRsaKey(int64_t minPrimeValue, int64_t maxPrimeValue);

#endif
