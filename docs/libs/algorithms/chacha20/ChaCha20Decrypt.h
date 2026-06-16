#pragma once

#include "ChaCha20Types.h"

ByteVec DecryptChaCha20(
    const ByteVec& ciphertext,
    const ByteVec& key,
    const ByteVec& nonce,
    uint32_t       counter = 0
);