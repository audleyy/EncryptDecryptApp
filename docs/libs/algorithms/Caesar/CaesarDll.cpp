#define CAESAR_DLL_EXPORTS
#include "CaesarDll.h"
#include "CaesarEncrypt.h"
#include "CaesarDecrypt.h"
#include "CaesarKeygen.h"
#include <cstring>
#include <vector>

using namespace std;

static int ValidateParams(const uint8_t* in, size_t in_len, uint8_t* out, size_t out_cap, size_t* out_len) {
    if (!in || !out || !out_len) return CAESAR_ERR_NULL_PTR;
    if (out_cap < in_len) return CAESAR_ERR_OUTPUT_SIZE;
    return CAESAR_OK;
}

extern "C" {

int CaesarEncryptDll(const uint8_t* in, size_t in_len, int shift, uint8_t* out, size_t out_cap, size_t* out_len) {
    int check = ValidateParams(in, in_len, out, out_cap, out_len);
    if (check != CAESAR_OK) return check;
    vector<uint8_t> result = CaesarEncrypt(vector<uint8_t>(in, in + in_len), CaesarKey{shift});
    memcpy(out, result.data(), result.size());
    *out_len = result.size();
    return CAESAR_OK;
}

int CaesarDecryptDll(const uint8_t* in, size_t in_len, int shift, uint8_t* out, size_t out_cap, size_t* out_len) {
    int check = ValidateParams(in, in_len, out, out_cap, out_len);
    if (check != CAESAR_OK) return check;
    vector<uint8_t> result = CaesarDecrypt(vector<uint8_t>(in, in + in_len), CaesarKey{shift});
    memcpy(out, result.data(), result.size());
    *out_len = result.size();
    return CAESAR_OK;
}

int CaesarGenerateKeyDll(int* outShift) {
    if (!outShift) return CAESAR_ERR_NULL_PTR;
    *outShift = CaesarGenerateKey().shift;
    return CAESAR_OK;
}

const char* CaesarStatusStr(int status) {
    switch (status) {
        case CAESAR_OK: return "OK";
        case CAESAR_ERR_NULL_PTR: return "Нулевой указатель";
        case CAESAR_ERR_OUTPUT_SIZE: return "Недостаточный размер буфера";
        default: return "Неизвестная ошибка";
    }
}

}
