#ifndef EL_GAMAL_BLOCK_CONVERTER_H
#define EL_GAMAL_BLOCK_CONVERTER_H

#include "../../algorithms/ElGamal/ElGamal.h"
#include <cstdint>
#include <vector>
#include <stdexcept>

using namespace std;

const size_t ElGamalBlockSize = sizeof(uint64_t) * 2;

vector<uint8_t> ElGamalBlocksToBytes(const vector<EncryptedBlockElGamal>& blocks);
vector<EncryptedBlockElGamal> BytesToElGamalBlocks(const vector<uint8_t>& bytes);

#endif
