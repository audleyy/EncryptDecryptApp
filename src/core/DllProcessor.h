#ifndef DLL_PROCESSOR_H
#define DLL_PROCESSOR_H

#include "../../libs/algorithms/ElGamalKeygen/ElGamalKeygen.h"
#include "../../libs/algorithms/CaesarKeygen/CaesarKeygen.h"
#include "../../libs/algorithms/RsaKeygen/RsaKeygen.h"
#include "../../libs/algorithms/ShamirKeygen/ShamirKeygen.h"
#include <cstdint>
#include <vector>

using namespace std;

vector<uint8_t> EncryptRsaByDll(const vector<uint8_t>& inputBytes, const RsaKey& key);
vector<uint8_t> DecryptRsaByDll(const vector<uint8_t>& inputBytes, const RsaKey& key);

vector<uint8_t> EncryptShamirByDll(const vector<uint8_t>& inputBytes, const ShamirKey& key);
vector<uint8_t> DecryptShamirByDll(const vector<uint8_t>& inputBytes, const ShamirKey& key);

vector<uint8_t> EncryptElGamalByDll(const vector<uint8_t>& inputBytes, const ElGamalKey& key);
vector<uint8_t> DecryptElGamalByDll(const vector<uint8_t>& inputBytes, const ElGamalKey& key);

vector<uint8_t> EncryptCaesarByDll(const vector<uint8_t>& inputBytes, const CaesarKey& key);
vector<uint8_t> DecryptCaesarByDll(const vector<uint8_t>& inputBytes, const CaesarKey& key);

#endif
