#include "../TestUtils/TestUtils.h"
#include "../libs/algorithms/RsaKeygen/RsaKeygen.h"
#include <cstdint>
#include <dlfcn.h>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

using RsaEncryptFunc = int (*)(const uint8_t*, size_t, int64_t, int64_t, uint8_t*, size_t, size_t*);
using RsaDecryptFunc = int (*)(const uint8_t*, size_t, int64_t, int64_t, uint8_t*, size_t, size_t*);

template <typename FuncType>
FuncType LoadRsaFunction(void* library, const string& functionName) {
    void* functionPointer = dlsym(library, functionName.c_str());
    if (functionPointer == nullptr) {
        throw runtime_error("Не удалось загрузить функцию RSA DLL: " + functionName);
    }
    return reinterpret_cast<FuncType>(functionPointer);
}

void TestRsaDllRoundTrip() {
    void* library = dlopen("bin/librsa.dylib", RTLD_LAZY);
    if (library == nullptr) {
        throw runtime_error("Не удалось открыть RSA DLL");
    }
    try {
        RsaEncryptFunc encryptFunc = LoadRsaFunction<RsaEncryptFunc>(library, "encrypt");
        RsaDecryptFunc decryptFunc = LoadRsaFunction<RsaDecryptFunc>(library, "decrypt");
        RsaKey key = GenerateRsaKey(17, 23, 3);
        vector<uint8_t> inputBytes = {72, 101, 108, 108, 111};
        vector<uint8_t> encryptedBytes(inputBytes.size() * sizeof(int64_t));
        size_t encryptedSize = 0;
        int encryptCode = encryptFunc(inputBytes.data(), inputBytes.size(), key.publicKey, key.moduleValue, encryptedBytes.data(), encryptedBytes.size(), &encryptedSize);
        CheckTest(encryptCode == 0, "RSA DLL: шифрование");
        encryptedBytes.resize(encryptedSize);
        vector<uint8_t> decryptedBytes(inputBytes.size());
        size_t decryptedSize = 0;
        int decryptCode = decryptFunc(encryptedBytes.data(), encryptedBytes.size(), key.privateKey, key.moduleValue, decryptedBytes.data(), decryptedBytes.size(), &decryptedSize);
        CheckTest(decryptCode == 0, "RSA DLL: расшифрование");
        decryptedBytes.resize(decryptedSize);
        CheckTest(decryptedBytes == inputBytes, "RSA DLL: полный цикл");
    } catch (...) {
        dlclose(library);
        throw;
    }
    dlclose(library);
}
