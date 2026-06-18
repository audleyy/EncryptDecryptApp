#pragma once
#include "ChaCha20Types.h"

using namespace std;

ByteVec ChaCha20Decrypt(const ByteVec& ciphertext, const ByteVec& key, const ByteVec& nonce, uint32_t counter = 0);