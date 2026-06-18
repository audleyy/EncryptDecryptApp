#define CAESAR_DLL_EXPORTS
#include "CaesarDll.h"

using namespace std;

static int validateParams(const uint8_t* in, size_t in_len, uint8_t* out, size_t out_cap, size_t* out_len) {
    if (!in || !out || !out_len) return InvalidInput;
    if (out_cap < in_len) return BufferTooSmall;
    return Success;
}

extern "C" {

int caesar_encrypt(const uint8_t* in, size_t in_len, uint64_t shift, uint8_t* out, size_t out_cap, size_t* out_len) {
    try {
        int check = validateParams(in, in_len, out, out_cap, out_len);
        if (check != Success) return check;
        vector<uint8_t> result = EncryptCaesar(vector<uint8_t>(in, in + in_len), shift);
        memcpy(out, result.data(), result.size());
        *out_len = result.size();
        return Success;
    } catch (...) {
        return CryptoError;
    }
}

int caesar_decrypt(const uint8_t* in, size_t in_len, uint64_t shift, uint8_t* out, size_t out_cap, size_t* out_len) {
    try {
        int check = validateParams(in, in_len, out, out_cap, out_len);
        if (check != Success) return check;
        vector<uint8_t> result = DecryptCaesar(vector<uint8_t>(in, in + in_len), shift);
        memcpy(out, result.data(), result.size());
        *out_len = result.size();
        return Success;
    } catch (...) {
        return CryptoError;
    }
}

const char* caesar_status_str(int status) {
    switch (status) {
        case Success: return "OK";
        case InvalidInput: return "Некорректные входные данные";
        case BufferTooSmall: return "Недостаточный размер буфера";
        case CryptoError: return "Ошибка шифрования или расшифрования";
        default: return "Неизвестная ошибка";
    }
}

}
