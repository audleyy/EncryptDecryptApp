#include "../../libs/algorithms/ShamirKeygen/ShamirKeygen.h"
#include <cassert>
#include <cstdint>
#include <dlfcn.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

using ShamirEncryptFunc = int (*)(const uint8_t*, size_t, int64_t, int64_t, int64_t, uint8_t*, size_t, size_t*);
using ShamirDecryptFunc = int (*)(const uint8_t*, size_t, int64_t, int64_t, int64_t, uint8_t*, size_t, size_t*);

template <typename FuncType>
FuncType LoadShamirFunction(void* library, const string& functionName) {
    void* functionPointer = dlsym(library, functionName.c_str());
    if (functionPointer == nullptr) {
        throw runtime_error("Не удалось загрузить функцию Shamir DLL: " + functionName);
    }
    return reinterpret_cast<FuncType>(functionPointer);
}

void TestShamirDllRoundTrip() {
    void* library = dlopen("bin/libshamir.dylib", RTLD_LAZY);
    if (library == nullptr) {
        throw runtime_error("Не удалось открыть Shamir DLL");
    }
    try {
        ShamirEncryptFunc encryptFunc = LoadShamirFunction<ShamirEncryptFunc>(library, "encrypt");
        ShamirDecryptFunc decryptFunc = LoadShamirFunction<ShamirDecryptFunc>(library, "decrypt");
        ShamirKey key = GenerateShamirKey(257, 3, 5);
        vector<uint8_t> inputBytes = {72, 101, 108, 108, 111};
        vector<uint8_t> encryptedBytes(inputBytes.size() * sizeof(int64_t));
        size_t encryptedSize = 0;
        int encryptCode = encryptFunc(inputBytes.data(), inputBytes.size(), key.primeValue, key.caValue, key.cbValue, encryptedBytes.data(), encryptedBytes.size(), &encryptedSize);
        cout << "Проверяем: Шамир DLL: шифрование\n";
        assert(encryptCode == 0);

        encryptedBytes.resize(encryptedSize);
        vector<uint8_t> decryptedBytes(inputBytes.size());
        size_t decryptedSize = 0;
        int decryptCode = decryptFunc(encryptedBytes.data(), encryptedBytes.size(), key.primeValue, key.daValue, key.dbValue, decryptedBytes.data(), decryptedBytes.size(), &decryptedSize);
        cout << "Проверяем: Шамир DLL: расшифрование\n";
        assert(decryptCode == 0);

        decryptedBytes.resize(decryptedSize);
        cout << "Проверяем: Шамир DLL: полный цикл\n";
        assert(decryptedBytes == inputBytes);
    } catch (...) {
        dlclose(library);
        throw;
    }
    dlclose(library);
}
