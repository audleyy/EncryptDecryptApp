#ifndef SHAMIR_H
#define SHAMIR_H

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

int64_t CalculateShamirX1(int64_t messageValue, int64_t caValue, int64_t primeValue);
int64_t CalculateShamirX2(int64_t x1Value, int64_t cbValue, int64_t primeValue);
int64_t CalculateShamirX3(int64_t x2Value, int64_t daValue, int64_t primeValue);
int64_t CalculateShamirX4(int64_t x3Value, int64_t dbValue, int64_t primeValue);
vector<uint8_t> EncryptShamir(const vector<uint8_t>& inputBytes, int64_t primeValue, int64_t caValue, int64_t cbValue);
vector<uint8_t> DecryptShamir(const vector<uint8_t>& inputBytes, int64_t primeValue, int64_t daValue, int64_t dbValue);

#endif
