#define CHACHA20_DLL_EXPORTS
#include "ChaCha20Dll.h"

int ValidateChaCha20DllParams(const uint8_t* inputBytes, size_t inputSize, const uint8_t* keyBytes, const uint8_t* nonceBytes, const uint8_t* outputBytes, size_t outputCapacity, const size_t* outputSize) {
    if (inputBytes == nullptr || keyBytes == nullptr || nonceBytes == nullptr || outputBytes == nullptr || outputSize == nullptr) {
        return InvalidInput;
    }
    if (outputCapacity < inputSize) {
        return BufferTooSmall;
    }
    return Success;
}

extern "C" {

int chacha20_encrypt(const uint8_t* inputBytes, size_t inputSize, const uint8_t* keyBytes, const uint8_t* nonceBytes, uint32_t counter, uint8_t* outputBytes, size_t outputCapacity, size_t* outputSize) {
    int errorCode = ValidateChaCha20DllParams(inputBytes, inputSize, keyBytes, nonceBytes, outputBytes, outputCapacity, outputSize);
    if (errorCode != Success) {
        return errorCode;
    }

    uint32_t state[16];
    uint8_t buffer[CHACHA20_BLOCK_SIZE];
    size_t bufferPos = CHACHA20_BLOCK_SIZE;

    try {
        ChaCha20InitContext(state, buffer, &bufferPos, keyBytes, nonceBytes, counter);
        ChaCha20XorRaw(state, buffer, &bufferPos, inputBytes, outputBytes, inputSize);
        *outputSize = inputSize;
    } catch (const invalid_argument&) {
        ChaCha20ClearRaw(state, buffer, &bufferPos);
        return InvalidInput;
    } catch (...) {
        ChaCha20ClearRaw(state, buffer, &bufferPos);
        return CryptoError;
    }

    ChaCha20ClearRaw(state, buffer, &bufferPos);
    return Success;
}

int chacha20_decrypt(const uint8_t* inputBytes, size_t inputSize, const uint8_t* keyBytes, const uint8_t* nonceBytes, uint32_t counter, uint8_t* outputBytes, size_t outputCapacity, size_t* outputSize) {
    return chacha20_encrypt(inputBytes, inputSize, keyBytes, nonceBytes, counter, outputBytes, outputCapacity, outputSize);
}

const char* chacha20_status_str(int status) {
    switch (status) {
        case Success: return "OK";
        case InvalidInput: return "Некорректные входные данные";
        case BufferTooSmall: return "Недостаточный размер буфера";
        case CryptoError: return "Ошибка шифрования или расшифрования";
        default: return "Неизвестная ошибка";
    }
}

}
