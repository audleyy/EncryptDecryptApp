#pragma once

#include "ChaCha20Types.h"

ByteVec EncryptChaCha20(
    const ByteVec& plaintext,
    const ByteVec& key,
    const ByteVec& nonce,
    uint32_t       counter = 0
);