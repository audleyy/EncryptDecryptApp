#pragma once
#include "../../../src/common/CommonTypes.h"
#include <cstdint>
#include <cstddef>

#ifdef _WIN32
    #ifdef CHACHA20_DLL_EXPORTS
        #define CHACHA20_API __declspec(dllexport)
    #else
        #define CHACHA20_API __declspec(dlimport)
    #endif
#else
    #define CHACHA20_API __attribute__((visibility("default")))
#endif

extern "C" {
    CHACHA20_API int chacha20_encrypt(const uint8_t* inputBytes, size_t inputSize, const uint8_t* keyBytes, const uint8_t* nonceBytes, uint32_t counter, uint8_t* outputBytes, size_t outputCapacity, size_t* outputSize);
    CHACHA20_API int chacha20_decrypt(const uint8_t* inputBytes, size_t inputSize, const uint8_t* keyBytes, const uint8_t* nonceBytes, uint32_t counter, uint8_t* outputBytes, size_t outputCapacity, size_t* outputSize);
    CHACHA20_API const char* chacha20_status_str(int status);
}
