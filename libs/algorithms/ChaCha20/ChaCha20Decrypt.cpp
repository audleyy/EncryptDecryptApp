#include "ChaCha20Decrypt.h"
#include "ChaCha20Encrypt.h"

using namespace std;

ByteVec ChaCha20Decrypt(const ByteVec& ciphertext, const ByteVec& key, const ByteVec& nonce, uint32_t counter) {
    return ChaCha20Encrypt(ciphertext, key, nonce, counter);
}