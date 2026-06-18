#ifndef KEY_FILE_H
#define KEY_FILE_H

#include "../../algorithms/RsaKeygen/RsaKeygen.h"
#include "../../algorithms/ShamirKeygen/ShamirKeygen.h"
#include "../../algorithms/ElGamalKeygen/ElGamalKeygen.h"
#include "../../algorithms/CaesarKeygen/CaesarKeygen.h"
#include "../../algorithms/ChaCha20Keygen/ChaCha20Keygen.h"

#include "../BinaryFile.h"
#include "../ConvertUtils.h"

#include <cstdint>
#include <string>
#include <vector>

using namespace std;

const uint64_t RsaAlgorithmId = 1;
const uint64_t ShamirAlgorithmId = 2;
const uint64_t ElGamalAlgorithmId = 3;
const uint64_t CaesarAlgorithmId = 4;
const uint64_t ChaCha20AlgorithmId = 5;

void SaveKeyNumbersToFile(const string& filePath, const vector<uint64_t>& keyNumbers);
vector<uint64_t> ReadKeyNumbersFromFile(const string& filePath);

void SaveRsaKeyToFile(const string& filePath, const RsaKey& key);
RsaKey ReadRsaKeyFromFile(const string& filePath);

void SaveShamirKeyToFile(const string& filePath, const ShamirKey& key);
ShamirKey ReadShamirKeyFromFile(const string& filePath);

void SaveElGamalKeyToFile(const string& filePath, const ElGamalKey& key);
ElGamalKey ReadElGamalKeyFromFile(const string& filePath);

void SaveCaesarKeyToFile(const string& filePath, const CaesarKey& key);
CaesarKey ReadCaesarKeyFromFile(const string& filePath);

void SaveChaCha20KeyToFile(const string& filePath, const ChaCha20Key& key);
ChaCha20Key ReadChaCha20KeyFromFile(const string& filePath);

void SaveDhChaCha20ParamsToFile(const string& filePath, const DhChaCha20Params& params);
DhChaCha20Params ReadDhChaCha20ParamsFromFile(const string& filePath);

#endif
