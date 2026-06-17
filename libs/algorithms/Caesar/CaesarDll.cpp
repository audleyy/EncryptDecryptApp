#define CAESAR_DLL_EXPORTS
#include "CaesarDll.h"
#include "CaesarEncrypt.h"
#include "CaesarDecrypt.h"
#include <cstring>
#include <vector>

using namespace std;

static int validateParams(const uint8_t* in, size_t in_len, uint8_t* out, size_t out_cap, size_t* out_len) {
    if (!in || !out || !out_len) return CAESAR_ERR_NULL_PTR;
    if (out_cap < in_len) return CAESAR_ERR_OUTPUT_SIZE;
    return CAESAR_OK;
}

extern "C" {

int caesar_encrypt(const uint8_t* in, size_t in_len, uint64_t shift, uint8_t* out, size_t out_cap, size_t* out_len) {
    int check = validateParams(in, in_len, out, out_cap, out_len);
    if (check != CAESAR_OK) return check;
    vector<uint8_t> result = EncryptCaesar(vector<uint8_t>(in, in + in_len), shift);
    memcpy(out, result.data(), result.size());
    *out_len = result.size();
    return CAESAR_OK;
}

int caesar_decrypt(const uint8_t* in, size_t in_len, uint64_t shift, uint8_t* out, size_t out_cap, size_t* out_len) {
    int check = validateParams(in, in_len, out, out_cap, out_len);
    if (check != CAESAR_OK) return check;
    vector<uint8_t> result = DecryptCaesar(vector<uint8_t>(in, in + in_len), shift);
    memcpy(out, result.data(), result.size());
    *out_len = result.size();
    return CAESAR_OK;
}

const char* caesar_status_str(int status) {
    switch (status) {
        case CAESAR_OK: return "OK";
        case CAESAR_ERR_NULL_PTR: return "Нулевой указатель";
        case CAESAR_ERR_OUTPUT_SIZE: return "Недостаточный размер буфера";
        default: return "Неизвестная ошибка";
    }
}

}
