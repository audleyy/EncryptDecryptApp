#define CHACHA20_DLL_EXPORTS
#include "ChaCha20Dll.h"
#include <cstring>
#include <exception>

// Прототипы функций Си-стиля из первого файла
void chacha20_init_context(uint32_t* state, uint8_t* buffer, size_t* buffer_pos, const uint8_t* key, const uint8_t* nonce, uint32_t counter);
void chacha20_xor_raw(uint32_t* state, uint8_t* buffer, size_t* buffer_pos, const uint8_t* input, uint8_t* output, size_t length);
void chacha20_clear_raw(uint32_t* state, uint8_t* buffer, size_t* buffer_pos);

static int validateParams(const uint8_t* in, size_t in_len, const uint8_t* key, const uint8_t* nonce, const uint8_t* out, size_t out_cap, const size_t* out_len) {
    if (!in || !key || !nonce || !out || !out_len) return CHACHA20_ERR_NULL_PTR;
    if (out_cap < in_len) return CHACHA20_ERR_OUTPUT_SIZE;
    return CHACHA20_OK;
}

extern "C" {

int chacha20_encrypt(const uint8_t* in, size_t in_len, const uint8_t* key, const uint8_t* nonce, uint32_t counter, uint8_t* out, size_t out_cap, size_t* out_len) {
    int check = validateParams(in, in_len, key, nonce, out, out_cap, out_len);
    if (check != CHACHA20_OK) return check;

    // Выделяем обычные локальные переменные на стеке вместо класса
    uint32_t state[16];
    uint8_t buffer[64];
    size_t buffer_pos = 64;

    try {
        chacha20_init_context(state, buffer, &buffer_pos, key, nonce, counter);
        chacha20_xor_raw(state, buffer, &buffer_pos, in, out, in_len);
        *out_len = in_len;
    } catch (...) {
        chacha20_clear_raw(state, buffer, &buffer_pos); // Зануляем вручную при ошибке
        return CHACHA20_ERR_COUNTER_OVERFLOW;
    }

    chacha20_clear_raw(state, buffer, &buffer_pos); // Зануляем вручную при успехе
    return CHACHA20_OK;
}

int chacha20_decrypt(const uint8_t* in, size_t in_len, const uint8_t* key, const uint8_t* nonce, uint32_t counter, uint8_t* out, size_t out_cap, size_t* out_len) {
    return chacha20_encrypt(in, in_len, key, nonce, counter, out, out_cap, out_len);
}

const char* chacha20_status_str(int status) {
    switch (status) {
        case CHACHA20_OK: return "OK";
        case CHACHA20_ERR_NULL_PTR: return "Нулевой указатель";
        case CHACHA20_ERR_OUTPUT_SIZE: return "Недостаточный размер буфера";
        case CHACHA20_ERR_COUNTER_OVERFLOW: return "Переполнение счётчика блоков";
        default: return "Неизвестная ошибка";
    }
}

}
