#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include <cstdint>
#include <string>

using namespace std;

enum class AlgorithmType {
    Rsa,
    Shamir,
    ElGamal,
    Caesar,
    ChaCha20
};

enum class OperationType {
    GenerateKey,
    Encrypt,
    Decrypt
};

enum ErrorCode {
    Success = 0,
    InvalidInput = 1,
    FileOpenError = 2,
    FileReadError = 3,
    FileWriteError = 4,
    KeyError = 5,
    CryptoError = 6,
    BufferTooSmall = 7,
    UnknownError = 100
};

struct CoreOptions {
    AlgorithmType algorithm;
    OperationType operation;
    bool useText;
    bool showNumbers;
    bool hasRsaManualParams;
    bool hasShamirManualParams;
    uint64_t pValue;
    uint64_t qValue;
    uint64_t cValue;
    uint64_t caValue;
    uint64_t cbValue;
    string inputFilePath;
    string outputFilePath;
    string keyFilePath;
    string textValue;
};

extern string LastErrorDetails;

#endif
