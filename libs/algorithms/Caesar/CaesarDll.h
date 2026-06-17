#pragma once
#include <cstdint>
#include <cstddef>

#ifdef _WIN32
    #ifdef CAESAR_DLL_EXPORTS
        #define CAESAR_API __declspec(dllexport)
    #else
        #define CAESAR_API __declspec(dllimport)
    #endif
#else
    #define CAESAR_API __attribute__((visibility("default")))
#endif

enum CaesarStatus {
    CAESAR_OK = 0,
    CAESAR_ERR_NULL_PTR = -1,
    CAESAR_ERR_OUTPUT_SIZE = -2
};

extern "C" {
    CAESAR_API int caesar_encrypt(const uint8_t* input, size_t input_len, uint64_t shift, uint8_t* output, size_t output_cap, size_t* output_len);
    CAESAR_API int caesar_decrypt(const uint8_t* input, size_t input_len, uint64_t shift, uint8_t* output, size_t output_cap, size_t* output_len);
    CAESAR_API const char* caesar_status_str(int status);
}
