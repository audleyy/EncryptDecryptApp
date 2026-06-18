#ifndef RSA_H
#define RSA_H

#include "../../helpers/ConvertUtils.h"
#include "../MathCrypto/CryptoUtils.h"


#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

uint64_t EncryptRsaByte(uint64_t messageValue, uint64_t publicKey, uint64_t moduleValue);
uint64_t DecryptRsaByte(uint64_t cipherValue, uint64_t privateKey, uint64_t moduleValue);
vector<uint8_t> EncryptRsa(const vector<uint8_t>& inputBytes, uint64_t publicKey, uint64_t moduleValue);
vector<uint8_t> DecryptRsa(const vector<uint8_t>& inputBytes, uint64_t privateKey, uint64_t moduleValue);

#endif
