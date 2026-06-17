#pragma once

#include "ChaCha20Types.h"

struct ChaCha20Key {
    ByteVec key;
    ByteVec nonce;
};

ChaCha20Key ChaCha20GenerateKey();