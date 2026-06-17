#include "TestCaesarDLL.h"
#include "../TestUtils/TestUtils.h"
#include <cassert>
#include <cstring>
#include <dlfcn.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

using EncryptCaesarFn = int(*)(const uint8_t*, size_t, int, uint8_t*, size_t, size_t*);
using DecryptCaesarFn = int(*)(const uint8_t*, size_t, int, uint8_t*, size_t, size_t*);

void RunCaesarDllTests() {
    cout << "\n--- Caesar DLL тесты ---\n";
    void* library = dlopen("./libcaesar.dylib", RTLD_LAZY);
    if (!library) throw runtime_error(string("Не удалось загрузить libcaesar.so: ") + dlerror());
    try {
        auto encryptFunc = (EncryptCaesarFn)dlsym(library, "caesar_encrypt");
        auto decryptFunc = (DecryptCaesarFn)dlsym(library, "caesar_decrypt");
        if (!encryptFunc || !decryptFunc) throw runtime_error("Не найдены функции в DLL");
        {
            string msg = "Hello DLL Caesar!";
            int shift = 7;
            size_t len = msg.size();
            vector<uint8_t> inputBytes(msg.begin(), msg.end());
            vector<uint8_t> encrypted(len), decrypted(len);
            size_t encSize = 0, decSize = 0;
            cout << "Проверяем: Caesar DLL: шифрование\n";
            int encCode = encryptFunc(inputBytes.data(), len, shift, encrypted.data(), encrypted.size(), &encSize);
            assert(encCode == 0);
            CheckTest(encCode == 0, "Caesar DLL: шифрование");
            encrypted.resize(encSize);
            cout << "Проверяем: Caesar DLL: расшифрование\n";
            int decCode = decryptFunc(encrypted.data(), encSize, shift, decrypted.data(), decrypted.size(), &decSize);
            assert(decCode == 0);
            CheckTest(decCode == 0, "Caesar DLL: расшифрование");
            decrypted.resize(decSize);
            cout << "Проверяем: Caesar DLL: полный цикл\n";
            assert(decrypted == inputBytes);
            CheckTest(decrypted == inputBytes, "Caesar DLL: полный цикл");
        }
        {
            uint8_t buf[32] = {};
            size_t sz = 0;
            cout << "Проверяем: Caesar DLL: нулевой input\n";
            int code = encryptFunc(nullptr, 10, 3, buf, sizeof(buf), &sz);
            assert(code != 0);
            CheckTest(code != 0, "Caesar DLL: нулевой input");
        }
    } catch (...) {
        dlclose(library);
        throw;
    }
    dlclose(library);
}
