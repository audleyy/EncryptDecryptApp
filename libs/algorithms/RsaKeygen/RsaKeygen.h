#ifndef RSA_KEYGEN_H
#define RSA_KEYGEN_H

#include <cstdint>
#include <stdexcept>
#include <string>

using namespace std;

struct RsaKey {
    uint64_t pValue;
    uint64_t qValue;
    uint64_t moduleValue;
    uint64_t phiValue;
    uint64_t privateKey;
    uint64_t publicKey;
};

uint64_t CalculateRsaModule(uint64_t pValue, uint64_t qValue);
uint64_t CalculateRsaPhi(uint64_t pValue, uint64_t qValue);
bool IsRsaPrivateKeyValid(uint64_t privateKey, uint64_t phiValue);
uint64_t CalculateRsaPublicKey(uint64_t privateKey, uint64_t phiValue);
RsaKey GenerateRsaKey(uint64_t pValue, uint64_t qValue, uint64_t privateKey);
uint64_t GenerateRandomRsaPrivateKey(uint64_t phiValue);
RsaKey GenerateRandomRsaKey(uint64_t minPrimeValue, uint64_t maxPrimeValue);

#endif
