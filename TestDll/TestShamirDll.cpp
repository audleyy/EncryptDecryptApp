#include "../TestUtils/TestUtils.h"
#include "../libs/algorithms/ShamirKeygen/ShamirKeygen.h"
#include <cstdint>
#include <dlfcn.h>
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
        CheckTest(encryptCode == 0, "Шамир DLL: шифрование");
        encryptedBytes.resize(encryptedSize);
        vector<uint8_t> decryptedBytes(inputBytes.size());
        size_t decryptedSize = 0;
        int decryptCode = decryptFunc(encryptedBytes.data(), encryptedBytes.size(), key.primeValue, key.daValue, key.dbValue, decryptedBytes.data(), decryptedBytes.size(), &decryptedSize);
        CheckTest(decryptCode == 0, "Шамир DLL: расшифрование");
        decryptedBytes.resize(decryptedSize);
        CheckTest(decryptedBytes == inputBytes, "Шамир DLL: полный цикл");
    } catch (...) {
        dlclose(library);
        throw;
    }
    dlclose(library);
}
