#ifndef KEY_FILE_H
#define KEY_FILE_H

#include "../../algorithms/RsaKeygen/RsaKeygen.h"
#include "../../algorithms/ShamirKeygen/ShamirKeygen.h"
#include "../../algorithms/ElGamalKeygen/ElGamalKeygen.h"
#include <cstdint>
#include <string>
#include <vector>

using namespace std;

const uint64_t RsaAlgorithmId = 1;
const uint64_t ShamirAlgorithmId = 2;
const uint64_t ElGamalAlgorithmId = 3;

void SaveKeyNumbersToFile(const string& filePath, const vector<uint64_t>& keyNumbers);
vector<uint64_t> ReadKeyNumbersFromFile(const string& filePath);

void SaveRsaKeyToFile(const string& filePath, const RsaKey& key);
RsaKey ReadRsaKeyFromFile(const string& filePath);

void SaveShamirKeyToFile(const string& filePath, const ShamirKey& key);
ShamirKey ReadShamirKeyFromFile(const string& filePath);

void SaveElGamalKeyToFile(const string& filePath, const ElGamalKey& key);
ElGamalKey ReadElGamalKeyFromFile(const string& filePath);

#endif
