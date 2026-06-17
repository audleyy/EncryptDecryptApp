#include "Core.h"
#include "StreamProcessor.h"
#include "../../libs/algorithms/RsaKeygen/RsaKeygen.h"
#include "../../libs/algorithms/ShamirKeygen/ShamirKeygen.h"
#include "../../libs/algorithms/ElGamalKeygen/ElGamalKeygen.h"
#include "../../libs/helpers/KeyFile/KeyFile.h"
#include <exception>

ErrorCode GenerateKeyByOptions(const CoreOptions& options) {
    ErrorCode errorCode = Success;

    if (options.keyFilePath.empty()) {
        errorCode = InvalidInput;
    } else {
        switch (options.algorithm) {
            case AlgorithmType::Rsa: {
                RsaKey key = GenerateRandomRsaKey(17, 61);
                SaveRsaKeyToFile(options.keyFilePath, key);
                break;
            }
            case AlgorithmType::Shamir: {
                ShamirKey key = GenerateRandomShamirKey(257, 313);
                SaveShamirKeyToFile(options.keyFilePath, key);
                break;
            }
            case AlgorithmType::ElGamal: {
                ElGamalKey key = GenerateRandomElGamalKey();
                SaveElGamalKeyToFile(options.keyFilePath, key);
                break;
            }
            default:
                errorCode = InvalidInput;
                break;
        }
    }
    return errorCode;
}

ErrorCode EncryptByOptions(const CoreOptions& options) {
    ErrorCode errorCode = Success;
    if (options.inputFilePath.empty() || options.outputFilePath.empty() || options.keyFilePath.empty()) {
        errorCode = InvalidInput;
    } else {
        switch (options.algorithm) {
            case AlgorithmType::Rsa:
                EncryptRsaFileByStream(options);
                break;
            case AlgorithmType::Shamir:
                EncryptShamirFileByStream(options);
                break;
            case AlgorithmType::ElGamal:
                EncryptElGamalFileByStream(options);
                break;
            default:
                errorCode = InvalidInput;
                break;
        }
    }
    return errorCode;
}

ErrorCode DecryptByOptions(const CoreOptions& options) {
    ErrorCode errorCode = Success;
    if (options.inputFilePath.empty() || options.outputFilePath.empty() || options.keyFilePath.empty()) {
        errorCode = InvalidInput;
    } else {
        switch (options.algorithm) {
            case AlgorithmType::Rsa:
                DecryptRsaFileByStream(options);
                break;
            case AlgorithmType::Shamir:
                DecryptShamirFileByStream(options);
                break;
            case AlgorithmType::ElGamal:
                DecryptElGamalFileByStream(options);
                break;
            default:
                errorCode = InvalidInput;
                break;
        }
    }
    return errorCode;
}

ErrorCode RunCore(const CoreOptions& options) {
    ErrorCode errorCode = Success;
    try {
        switch (options.operation) {
            case OperationType::GenerateKey:
                errorCode = GenerateKeyByOptions(options);
                break;
            case OperationType::Encrypt:
                errorCode = EncryptByOptions(options);
                break;
            case OperationType::Decrypt:
                errorCode = DecryptByOptions(options);
                break;
            default:
                errorCode = InvalidInput;
                break;
        }
    } catch (const invalid_argument&) {
        errorCode = InvalidInput;
    } catch (const runtime_error&) {
        errorCode = CryptoError;
    } catch (const exception&) {
        errorCode = UnknownError;
    }
    return errorCode;
}
