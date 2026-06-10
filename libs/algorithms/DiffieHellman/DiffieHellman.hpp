#ifndef DIFFIE_HELLMAN_H
#define DIFFIE_HELLMAN_H

#include <cstdint>
#include <stdexcept>
#include <string>

using namespace std;

struct KeyPairDh {
	uint64_t privateKey;
	uint64_t publicKey;
};

uint64_t CalculateModularExponentiation(uint64_t baseValue, uint64_t exponentValue, uint64_t modulusValue);

uint64_t GeneratePrivateKey(uint64_t minLimit, uint64_t maxLimit);

uint64_t GeneratePublicKey(uint64_t generatorValue, uint64_t privateKey, uint64_t primeModulus);

uint64_t GenerateSharedSecret(uint64_t otherPublicKey, uint64_t myPrivateKey, uint64_t primeModulus);

#endif