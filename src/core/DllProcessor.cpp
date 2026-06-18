#include "DllProcessor.h"

const string RsaLibraryPath = "bin/librsa.dylib";
const string ShamirLibraryPath = "bin/libshamir.dylib";
const string ElGamalLibraryPath = "bin/libelgamal.dylib";
const string CaesarLibraryPath = "bin/libcaesar.dylib";
const string ChaCha20LibraryPath = "bin/libchacha20.dylib";

struct DllLibrary {
    void* handle;
};

DllLibrary OpenDllLibrary(const string& libraryPath, const string& algorithmName) {
    DllLibrary library;
    library.handle = dlopen(libraryPath.c_str(), RTLD_NOW);
    if (library.handle == nullptr) {
        throw runtime_error("Не удалось открыть DLL " + algorithmName);
    }
    return library;
}

void CloseDllLibrary(DllLibrary& library) {
    if (library.handle != nullptr) {
        dlclose(library.handle);
        library.handle = nullptr;
    }
}

void* LoadDllFunction(const DllLibrary& library, const string& functionName, const string& algorithmName) {
    void* function = dlsym(library.handle, functionName.c_str());
    if (function == nullptr) {
        throw runtime_error("Не удалось получить функцию " + functionName + " из DLL " + algorithmName);
    }
    return function;
}

void CheckDllError(int errorCode) {
    if (errorCode == InvalidInput) {
        throw invalid_argument("DLL получила некорректные входные данные");
    } else if (errorCode == BufferTooSmall) {
        throw length_error("DLL получила недостаточный выходной буфер");
    } else if (errorCode != Success) {
        throw runtime_error("DLL вернула ошибку шифрования или расшифрования");
    }
}

vector<uint8_t> ProcessRsaByDll(const vector<uint8_t>& inputBytes, const RsaKey& key, bool isEncrypt) {
    using RsaEncryptFunction = int (*)(const uint8_t*, size_t, uint64_t, uint64_t, uint8_t*, size_t, size_t*);
    DllLibrary library = OpenDllLibrary(RsaLibraryPath, "RSA");
    string functionName = isEncrypt ? "encrypt" : "decrypt";
    RsaEncryptFunction function = reinterpret_cast<RsaEncryptFunction>(LoadDllFunction(library, functionName, "RSA"));
    size_t outputCapacity = isEncrypt ? inputBytes.size() * sizeof(uint64_t) : inputBytes.size() / sizeof(uint64_t);
    vector<uint8_t> outputBytes(outputCapacity);
    size_t outputSize = 0;
    uint64_t keyPower = isEncrypt ? key.publicKey : key.privateKey;
    int errorCode = function(inputBytes.data(), inputBytes.size(), keyPower, key.moduleValue, outputBytes.data(), outputBytes.size(), &outputSize);
    CloseDllLibrary(library);
    CheckDllError(errorCode);
    outputBytes.resize(outputSize);
    return outputBytes;
}

vector<uint8_t> ProcessShamirByDll(const vector<uint8_t>& inputBytes, const ShamirKey& key, bool isEncrypt) {
    using ShamirEncryptFunction = int (*)(const uint8_t*, size_t, uint64_t, uint64_t, uint64_t, uint8_t*, size_t, size_t*);

    DllLibrary library = OpenDllLibrary(ShamirLibraryPath, "Shamir");
    string functionName = isEncrypt ? "encrypt" : "decrypt";
    ShamirEncryptFunction function =
        reinterpret_cast<ShamirEncryptFunction>(LoadDllFunction(library, functionName, "Shamir"));

    size_t outputCapacity = isEncrypt ? inputBytes.size() * sizeof(uint64_t) : inputBytes.size() / sizeof(uint64_t);
    vector<uint8_t> outputBytes(outputCapacity);
    size_t outputSize = 0;
    uint64_t firstKey = isEncrypt ? key.caValue : key.daValue;
    uint64_t secondKey = isEncrypt ? key.cbValue : key.dbValue;
    int errorCode = function(inputBytes.data(), inputBytes.size(), key.primeValue, firstKey, secondKey, outputBytes.data(), outputBytes.size(), &outputSize);
    CloseDllLibrary(library);
    CheckDllError(errorCode);
    outputBytes.resize(outputSize);
    return outputBytes;
}

vector<uint8_t> ProcessElGamalByDll(const vector<uint8_t>& inputBytes, const ElGamalKey& key, bool isEncrypt) {
    using ElGamalEncryptFunction = int (*)(const uint8_t*, size_t, uint64_t, uint64_t, uint64_t, uint8_t*, size_t, size_t*);
    using ElGamalDecryptFunction = int (*)(const uint8_t*, size_t, uint64_t, uint64_t, uint8_t*, size_t, size_t*);
    DllLibrary library = OpenDllLibrary(ElGamalLibraryPath, "ElGamal");
    string functionName = isEncrypt ? "encrypt" : "decrypt";
    size_t outputCapacity = isEncrypt ? inputBytes.size() * ElGamalBlockSize : inputBytes.size() / ElGamalBlockSize;
    vector<uint8_t> outputBytes(outputCapacity);
    size_t outputSize = 0;
    int errorCode = 0;
    if (isEncrypt) {
        ElGamalEncryptFunction function =
            reinterpret_cast<ElGamalEncryptFunction>(LoadDllFunction(library, functionName, "ElGamal"));
        errorCode = function(inputBytes.data(), inputBytes.size(), key.primeModulus, key.generatorValue, key.publicKey, outputBytes.data(),outputBytes.size(), &outputSize);
    } else {
        ElGamalDecryptFunction function =
            reinterpret_cast<ElGamalDecryptFunction>(LoadDllFunction(library, functionName, "ElGamal"));
        errorCode = function(inputBytes.data(), inputBytes.size(), key.primeModulus, key.privateKey, outputBytes.data(), outputBytes.size(), &outputSize);
    }
    CloseDllLibrary(library);
    CheckDllError(errorCode);
    outputBytes.resize(outputSize);
    return outputBytes;
}

vector<uint8_t> ProcessCaesarByDll(const vector<uint8_t>& inputBytes, const CaesarKey& key, bool isEncrypt) {
    using CaesarFunction = int (*)(const uint8_t*, size_t, uint64_t, uint8_t*, size_t, size_t*);
    DllLibrary library = OpenDllLibrary(CaesarLibraryPath, "Caesar");
    string functionName = isEncrypt ? "caesar_encrypt" : "caesar_decrypt";
    CaesarFunction function = reinterpret_cast<CaesarFunction>(LoadDllFunction(library, functionName, "Caesar"));

    vector<uint8_t> outputBytes(inputBytes.size());
    size_t outputSize = 0;
    int errorCode = function(inputBytes.data(), inputBytes.size(), key.shift, outputBytes.data(), outputBytes.size(), &outputSize);

    CloseDllLibrary(library);
    CheckDllError(errorCode);
    outputBytes.resize(outputSize);
    return outputBytes;
}

vector<uint8_t> ProcessChaCha20ByDll(const vector<uint8_t>& inputBytes, const ChaCha20Key& key, bool isEncrypt) {
    using ChaCha20Function =
        int (*)(const uint8_t*, size_t, const uint8_t*, const uint8_t*, uint32_t, uint8_t*, size_t, size_t*);
    DllLibrary library = OpenDllLibrary(ChaCha20LibraryPath, "ChaCha20");
    string functionName = isEncrypt ? "chacha20_encrypt" : "chacha20_decrypt";
    ChaCha20Function function = reinterpret_cast<ChaCha20Function>(LoadDllFunction(library, functionName, "ChaCha20"));
    vector<uint8_t> outputBytes(inputBytes.size());
    size_t outputSize = 0;
    int errorCode = function(inputBytes.data(), inputBytes.size(), key.key.data(), key.nonce.data(), key.counter,
        outputBytes.data(), outputBytes.size(), &outputSize);

    CloseDllLibrary(library);
    CheckDllError(errorCode);
    outputBytes.resize(outputSize);
    return outputBytes;
}

vector<uint8_t> EncryptRsaByDll(const vector<uint8_t>& inputBytes, const RsaKey& key) {
    return ProcessRsaByDll(inputBytes, key, true);
}

vector<uint8_t> DecryptRsaByDll(const vector<uint8_t>& inputBytes, const RsaKey& key) {
    return ProcessRsaByDll(inputBytes, key, false);
}

vector<uint8_t> EncryptShamirByDll(const vector<uint8_t>& inputBytes, const ShamirKey& key) {
    return ProcessShamirByDll(inputBytes, key, true);
}

vector<uint8_t> DecryptShamirByDll(const vector<uint8_t>& inputBytes, const ShamirKey& key) {
    return ProcessShamirByDll(inputBytes, key, false);
}

vector<uint8_t> EncryptElGamalByDll(const vector<uint8_t>& inputBytes, const ElGamalKey& key) {
    return ProcessElGamalByDll(inputBytes, key, true);
}

vector<uint8_t> DecryptElGamalByDll(const vector<uint8_t>& inputBytes, const ElGamalKey& key) {
    return ProcessElGamalByDll(inputBytes, key, false);
}

vector<uint8_t> EncryptCaesarByDll(const vector<uint8_t>& inputBytes, const CaesarKey& key) {
    return ProcessCaesarByDll(inputBytes, key, true);
}

vector<uint8_t> DecryptCaesarByDll(const vector<uint8_t>& inputBytes, const CaesarKey& key) {
    return ProcessCaesarByDll(inputBytes, key, false);
}

vector<uint8_t> EncryptChaCha20ByDll(const vector<uint8_t>& inputBytes, const ChaCha20Key& key) {
    return ProcessChaCha20ByDll(inputBytes, key, true);
}

vector<uint8_t> DecryptChaCha20ByDll(const vector<uint8_t>& inputBytes, const ChaCha20Key& key) {
    return ProcessChaCha20ByDll(inputBytes, key, false);
}
