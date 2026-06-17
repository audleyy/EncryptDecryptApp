#include "TestChaCha20Dll.h"
#include "../TestUtils/TestUtils.h"
#include <cassert>
#include <cstring>
#include <dlfcn.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

using ChaCha20EncryptFn = int(*)(const uint8_t*, size_t, const uint8_t*, const uint8_t*, uint32_t, uint8_t*, size_t, size_t*);
using ChaCha20DecryptFn = int(*)(const uint8_t*, size_t, const uint8_t*, const uint8_t*, uint32_t, uint8_t*, size_t, size_t*);

static const uint8_t DLL_KEY[32] = {
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
    0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f
};
static const uint8_t DLL_NONCE[12] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4a,0x00,0x00,0x00,0x00};

// Имя функции должно быть строго таким, без опечаток:
void RunChaCha20DllTests() {
    cout << "\n--- ChaCha20 DLL тесты ---\n";
    void* library = dlopen("./libchacha20.dylib", RTLD_LAZY);
    if (!library) throw runtime_error(string("Не удалось загрузить libchacha20.dylib: ") + dlerror());
    try {
        auto encryptFunc = (ChaCha20EncryptFn)dlsym(library, "chacha20_encrypt");
        auto decryptFunc = (ChaCha20DecryptFn)dlsym(library, "chacha20_decrypt");
        if (!encryptFunc || !decryptFunc) throw runtime_error("Не найдены функции в DLL");
        {
            string msg = "Hello ChaCha20 DLL!";
            size_t len = msg.size();
            vector<uint8_t> inputBytes(msg.begin(), msg.end());
            vector<uint8_t> encrypted(len), decrypted(len);
            size_t encSize = 0, decSize = 0;
            cout << "Проверяем: ChaCha20 DLL: шифрование\n";
            int encCode = encryptFunc(inputBytes.data(), len, DLL_KEY, DLL_NONCE, 1, encrypted.data(), encrypted.size(), &encSize);
            assert(encCode == 0);
            CheckTest(encCode == 0, "ChaCha20 DLL: шифрование");
            encrypted.resize(encSize);
            cout << "Проверяем: ChaCha20 DLL: расшифрование\n";
            int decCode = decryptFunc(encrypted.data(), encSize, DLL_KEY, DLL_NONCE, 1, decrypted.data(), decrypted.size(), &decSize);
            assert(decCode == 0);
            CheckTest(decCode == 0, "ChaCha20 DLL: расшифрование");
            decrypted.resize(decSize);
            cout << "Проверяем: ChaCha20 DLL: полный цикл\n";
            assert(decrypted == inputBytes);
            CheckTest(decrypted == inputBytes, "ChaCha20 DLL: полный цикл");
        }
        {
            uint8_t buf[64] = {};
            size_t sz = 0;
            cout << "Проверяем: ChaCha20 DLL: нулевой input\n";
            int code = encryptFunc(nullptr, 16, DLL_KEY, DLL_NONCE, 0, buf, sizeof(buf), &sz);
            assert(code != 0);
            CheckTest(code != 0, "ChaCha20 DLL: нулевой input");
        }
        {
            uint8_t plain[32] = {}, output[8] = {};
            size_t sz = 0;
            cout << "Проверяем: ChaCha20 DLL: маленький буфер\n";
            int code = encryptFunc(plain, 32, DLL_KEY, DLL_NONCE, 0, output, sizeof(output), &sz);
            assert(code != 0);
            CheckTest(code != 0, "ChaCha20 DLL: маленький буфер");
        }
    } catch (...) {
        dlclose(library);
        throw;
    }
    dlclose(library);
}
