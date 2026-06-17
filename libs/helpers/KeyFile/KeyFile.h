#ifndef KEY_FILE_H
#define KEY_FILE_H

#include "../../algorithms/RsaKeygen/RsaKeygen.h"
#include "../../algorithms/ShamirKeygen/ShamirKeygen.h"
#include "../../algorithms/ElGamalKeygen/ElGamalKeygen.h"
#include <string>

using namespace std;

void SaveRsaKeyToFile(const string& filePath, const RsaKey& key);
RsaKey ReadRsaKeyFromFile(const string& filePath);

void SaveShamirKeyToFile(const string& filePath, const ShamirKey& key);
ShamirKey ReadShamirKeyFromFile(const string& filePath);

void SaveElGamalKeyToFile(const string& filePath, const ElGamalKey& key);
ElGamalKey ReadElGamalKeyFromFile(const string& filePath);

#endif
