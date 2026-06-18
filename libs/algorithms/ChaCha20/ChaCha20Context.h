#pragma once
#include "ChaCha20Types.h"
#include "ChaCha20Round.h"
#include <cstring>
#include <stdexcept>
#include <string>

using namespace std;

void ChaCha20InitContext(uint32_t* state, uint8_t* buffer, size_t* bufferPos, const uint8_t* key, const uint8_t* nonce, uint32_t counter);
void ChaCha20NextBlockRaw(uint32_t* state, uint8_t* buffer, size_t* bufferPos);
void ChaCha20XorRaw(uint32_t* state, uint8_t* buffer, size_t* bufferPos, const uint8_t* input, uint8_t* output, size_t length);
void ChaCha20ClearRaw(uint32_t* state, uint8_t* buffer, size_t* bufferPos);
void ChaCha20ValidateRaw(const ByteVec& key, const ByteVec& nonce);