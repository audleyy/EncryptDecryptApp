#include "Core.h"
#include "DllProcessor.h"
#include "StreamProcessor.h"
#include "../../libs/algorithms/RsaKeygen/RsaKeygen.h"
#include "../../libs/algorithms/ShamirKeygen/ShamirKeygen.h"
#include "../../libs/algorithms/ElGamalKeygen/ElGamalKeygen.h"
#include "../../libs/algorithms/CaesarKeygen/CaesarKeygen.h"
#include "../../libs/algorithms/ChaCha20Keygen/ChaCha20Keygen.h"
#include "../../libs/helpers/ConvertUtils.h"
#include "../../libs/helpers/KeyFile/KeyFile.h"
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

string LastErrorDetails;

ErrorCode ClassifyRuntimeError(const runtime_error& error) {
    string text = error.what();
    ErrorCode errorCode = CryptoError;
    if (text.find("ключ") != string::npos || text.find("ключа") != string::npos || text.find("ключом") != string::npos) {
        errorCode = KeyError;
    } else if (text.find("открыть файл") != string::npos || text.find("открыть библиотеку") != string::npos ||
        text.find("открыть DLL") != string::npos) {
        errorCode = FileOpenError;
    } else if (text.find("прочитать") != string::npos) {
        errorCode = FileReadError;
    } else if (text.find("записать") != string::npos) {
        errorCode = FileWriteError;
    }

    return errorCode;
}

void EncryptTextByOptions(const CoreOptions& options) {
    vector<uint8_t> inputBytes = TextToBytes(options.textValue);
    vector<uint8_t> outputBytes;
    switch (options.algorithm) {
        case AlgorithmType::Rsa: {
            RsaKey key = ReadRsaKeyFromFile(options.keyFilePath);
            outputBytes = EncryptRsaByDll(inputBytes, key);
            break;
        }
        case AlgorithmType::Shamir: {
            ShamirKey key = ReadShamirKeyFromFile(options.keyFilePath);
            outputBytes = EncryptShamirByDll(inputBytes, key);
            break;
        }
        case AlgorithmType::ElGamal: {
            ElGamalKey key = ReadElGamalKeyFromFile(options.keyFilePath);
            outputBytes = EncryptElGamalByDll(inputBytes, key);
            break;
        }
        case AlgorithmType::Caesar: {
            CaesarKey key = ReadCaesarKeyFromFile(options.keyFilePath);
            outputBytes = EncryptCaesarByDll(inputBytes, key);
            break;
        }
        case AlgorithmType::ChaCha20: {
            ChaCha20Key key = ReadChaCha20KeyFromFile(options.keyFilePath);
            outputBytes = EncryptChaCha20ByDll(inputBytes, key);
            break;
        }
        default:
            throw invalid_argument("Некорректный алгоритм");
    }
    cout << BytesToHex(outputBytes) << "\n";
}

void DecryptTextByOptions(const CoreOptions& options) {
    vector<uint8_t> inputBytes = HexToBytes(options.textValue);
    vector<uint8_t> outputBytes;
    switch (options.algorithm) {
        case AlgorithmType::Rsa: {
            RsaKey key = ReadRsaKeyFromFile(options.keyFilePath);
            outputBytes = DecryptRsaByDll(inputBytes, key);
            break;
        }
        case AlgorithmType::Shamir: {
            ShamirKey key = ReadShamirKeyFromFile(options.keyFilePath);
            outputBytes = DecryptShamirByDll(inputBytes, key);
            break;
        }
        case AlgorithmType::ElGamal: {
            ElGamalKey key = ReadElGamalKeyFromFile(options.keyFilePath);
            outputBytes = DecryptElGamalByDll(inputBytes, key);
            break;
        }
        case AlgorithmType::Caesar: {
            CaesarKey key = ReadCaesarKeyFromFile(options.keyFilePath);
            outputBytes = DecryptCaesarByDll(inputBytes, key);
            break;
        }
        case AlgorithmType::ChaCha20: {
            ChaCha20Key key = ReadChaCha20KeyFromFile(options.keyFilePath);
            outputBytes = DecryptChaCha20ByDll(inputBytes, key);
            break;
        }
        default:
            throw invalid_argument("Некорректный алгоритм");
    }

    cout << BytesToText(outputBytes) << "\n";
}

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
            case AlgorithmType::Caesar: {
                CaesarKey key = GenerateRandomCaesarKey();
                SaveCaesarKeyToFile(options.keyFilePath, key);
                break;
            }
            case AlgorithmType::ChaCha20: {
                ChaCha20Key key = GenerateRandomChaCha20Key();
                SaveChaCha20KeyToFile(options.keyFilePath, key);
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
    if (options.keyFilePath.empty()) {
        errorCode = InvalidInput;
    } else if (options.useText) {
        EncryptTextByOptions(options);
    } else if (options.inputFilePath.empty() || options.outputFilePath.empty()) {
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
            case AlgorithmType::Caesar:
                EncryptCaesarFileByStream(options);
                break;
            case AlgorithmType::ChaCha20:
                EncryptChaCha20FileByStream(options);
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
    if (options.keyFilePath.empty()) {
        errorCode = InvalidInput;
    } else if (options.useText) {
        DecryptTextByOptions(options);
    } else if (options.inputFilePath.empty() || options.outputFilePath.empty()) {
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
            case AlgorithmType::Caesar:
                DecryptCaesarFileByStream(options);
                break;
            case AlgorithmType::ChaCha20:
                DecryptChaCha20FileByStream(options);
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
    LastErrorDetails.clear();
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
    } catch (const invalid_argument& error) {
        LastErrorDetails = error.what();
        errorCode = InvalidInput;
    } catch (const length_error& error) {
        LastErrorDetails = error.what();
        errorCode = BufferTooSmall;
    } catch (const runtime_error& error) {
        LastErrorDetails = error.what();
        errorCode = ClassifyRuntimeError(error);
    } catch (const exception& error) {
        LastErrorDetails = error.what();
        errorCode = UnknownError;
    }
    return errorCode;
}
