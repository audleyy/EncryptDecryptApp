#ifndef SHAMIR_H
#define SHAMIR_H

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

uint64_t CalculateShamirX1(uint64_t messageValue, uint64_t caValue, uint64_t primeValue);
uint64_t CalculateShamirX2(uint64_t x1Value, uint64_t cbValue, uint64_t primeValue);
uint64_t CalculateShamirX3(uint64_t x2Value, uint64_t daValue, uint64_t primeValue);
uint64_t CalculateShamirX4(uint64_t x3Value, uint64_t dbValue, uint64_t primeValue);
vector<uint8_t> EncryptShamir(const vector<uint8_t>& inputBytes, uint64_t primeValue, uint64_t caValue, uint64_t cbValue);
vector<uint8_t> DecryptShamir(const vector<uint8_t>& inputBytes, uint64_t primeValue, uint64_t daValue, uint64_t dbValue);

#endif
