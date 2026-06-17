#include "ChaCha20Decrypt.h"
#include "ChaCha20Encrypt.h"
ByteVec DecryptChaCha20(const ByteVec& ciphertext, const ByteVec& key, const ByteVec& nonce, uint32_t counter) {
    return EncryptChaCha20(ciphertext, key, nonce, counter);
}
