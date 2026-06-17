#ifndef RSA_H
#define RSA_H

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

int64_t EncryptRsaByte(int64_t messageValue, int64_t publicKey, int64_t moduleValue);
int64_t DecryptRsaByte(int64_t cipherValue, int64_t privateKey, int64_t moduleValue);
vector<uint8_t> EncryptRsa(const vector<uint8_t>& inputBytes, int64_t publicKey, int64_t moduleValue);
vector<uint8_t> DecryptRsa(const vector<uint8_t>& inputBytes, int64_t privateKey, int64_t moduleValue);

#endif
