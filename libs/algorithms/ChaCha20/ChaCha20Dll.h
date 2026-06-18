#pragma once
#include "../../../src/common/CommonTypes.h"
#include "ChaCha20Types.h"
#include <cstring>
#include <exception>
#include <cstdint>
#include <cstddef>

using namespace std;

#ifdef _WIN32
    #ifdef CHACHA20_DLL_EXPORTS
        #define CHACHA20_API __declspec(dllexport)
    #else
        #define CHACHA20_API __declspec(dlimport)
    #endif
#else
    #define CHACHA20_API __attribute__((visibility("default")))
#endif

void ChaCha20ValidateRaw(const ByteVec& key, const ByteVec& nonce);
void ChaCha20InitContext(uint32_t* state, uint8_t* buffer, size_t* bufferPos, const uint8_t* key, const uint8_t* nonce, uint32_t counter);
void ChaCha20XorRaw(uint32_t* state, uint8_t* buffer, size_t* bufferPos, const uint8_t* input, uint8_t* output, size_t length);
void ChaCha20ClearRaw(uint32_t* state, uint8_t* buffer, size_t* bufferPos);

extern "C" {
    CHACHA20_API int chacha20_encrypt(const uint8_t* inputBytes, size_t inputSize, const uint8_t* keyBytes, const uint8_t* nonceBytes, uint32_t counter, uint8_t* outputBytes, size_t outputCapacity, size_t* outputSize);
    CHACHA20_API int chacha20_decrypt(const uint8_t* inputBytes, size_t inputSize, const uint8_t* keyBytes, const uint8_t* nonceBytes, uint32_t counter, uint8_t* outputBytes, size_t outputCapacity, size_t* outputSize);
    CHACHA20_API const char* chacha20_status_str(int status);
}
