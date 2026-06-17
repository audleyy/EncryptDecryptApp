#pragma once
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

enum ChaCha20Status {
    CHACHA20_OK = 0,
    CHACHA20_ERR_NULL_PTR = -1,
    CHACHA20_ERR_OUTPUT_SIZE = -2,
    CHACHA20_ERR_COUNTER_OVERFLOW = -3
};

extern "C" {
    CHACHA20_API int chacha20_encrypt(const uint8_t* input, size_t input_len, const uint8_t* key, const uint8_t* nonce, uint32_t counter, uint8_t* output, size_t output_cap, size_t* output_len);
    CHACHA20_API int chacha20_decrypt(const uint8_t* input, size_t input_len, const uint8_t* key, const uint8_t* nonce, uint32_t counter, uint8_t* output, size_t output_cap, size_t* output_len);
    CHACHA20_API const char* chacha20_status_str(int status);
}
