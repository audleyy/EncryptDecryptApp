#ifndef EL_GAMAL_H
#define EL_GAMAL_H

#include <cstdint>
#include <vector>
#include <stdexcept>
#include <string>

using namespace std;

struct EncryptedBlockElGamal {
	uint64_t firstHalf;
	uint64_t secondHalf;
};

EncryptedBlockElGamal EncryptBlockElGamal(uint64_t messageValue, uint64_t bobPublicKey, uint64_t primeModulus, uint64_t generatorValue);

uint64_t DecryptBlockElGamal(uint64_t c1, uint64_t c2, uint64_t bobPrivateKey, uint64_t primeModulus);

vector<EncryptedBlockElGamal> EncryptBytesElGamal(const vector<uint8_t>& inputData, uint64_t bobPublicKey, uint64_t primeModulus, uint64_t generatorValue);

vector<uint8_t> DecryptBytesElGamal(const vector<EncryptedBlockElGamal>& encryptedData, uint64_t bobPrivateKey, uint64_t primeModulus);

#endif