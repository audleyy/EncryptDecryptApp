#include "StreamProcessor.h"

const size_t OpenTextChunkSize = 4096;
const size_t CipherTextChunkSize = OpenTextChunkSize * sizeof(uint64_t);
const size_t ElGamalCipherTextChunkSize = OpenTextChunkSize * ElGamalBlockSize;

uint32_t CalculateNextChaCha20Counter(uint32_t currentCounter, size_t chunkSize) {
    size_t blockCount = (chunkSize + CHACHA20_BLOCK_SIZE - 1) / CHACHA20_BLOCK_SIZE;
    if (blockCount > CHACHA20_MAX_COUNTER - currentCounter) {
        throw runtime_error("ChaCha20: переполнение счетчика");
    }
    return currentCounter + blockCount;
}

void ProcessFileByStream(const CoreOptions& options, size_t chunkSize, const function<vector<uint8_t>(const vector<uint8_t>&)>& processChunk) {
    ifstream inputFile(options.inputFilePath, ios::binary);
    ofstream outputFile(options.outputFilePath, ios::binary);
    if (!inputFile || !outputFile) {
        throw runtime_error("Не удалось открыть файл");
    }
    vector<uint8_t> inputBytes = ReadBinaryChunk(inputFile, chunkSize);
    while (!inputBytes.empty()) {
        vector<uint8_t> outputBytes = processChunk(inputBytes);
        WriteBinaryChunk(outputFile, outputBytes);
        inputBytes = ReadBinaryChunk(inputFile, chunkSize);
    }
}

void EncryptRsaFileByStream(const CoreOptions& options) {
    RsaKey key = ReadRsaKeyFromFile(options.keyFilePath);
    ProcessFileByStream(options, OpenTextChunkSize, [&](const vector<uint8_t>& inputBytes) {
        return EncryptRsaByDll(inputBytes, key);
    });
}

void DecryptRsaFileByStream(const CoreOptions& options) {
    RsaKey key = ReadRsaKeyFromFile(options.keyFilePath);
    ProcessFileByStream(options, CipherTextChunkSize, [&](const vector<uint8_t>& inputBytes) {
        return DecryptRsaByDll(inputBytes, key);
    });
}

void EncryptShamirFileByStream(const CoreOptions& options) {
    ShamirKey key = ReadShamirKeyFromFile(options.keyFilePath);
    ProcessFileByStream(options, OpenTextChunkSize, [&](const vector<uint8_t>& inputBytes) {
        return EncryptShamirByDll(inputBytes, key);
    });
}

void DecryptShamirFileByStream(const CoreOptions& options) {
    ShamirKey key = ReadShamirKeyFromFile(options.keyFilePath);
    ProcessFileByStream(options, CipherTextChunkSize, [&](const vector<uint8_t>& inputBytes) {
        return DecryptShamirByDll(inputBytes, key);
    });
}

void EncryptElGamalFileByStream(const CoreOptions& options) {
    ElGamalKey key = ReadElGamalKeyFromFile(options.keyFilePath);
    ProcessFileByStream(options, OpenTextChunkSize, [&](const vector<uint8_t>& inputBytes) {
        return EncryptElGamalByDll(inputBytes, key);
    });
}

void DecryptElGamalFileByStream(const CoreOptions& options) {
    ElGamalKey key = ReadElGamalKeyFromFile(options.keyFilePath);
    ProcessFileByStream(options, ElGamalCipherTextChunkSize, [&](const vector<uint8_t>& inputBytes) {
        return DecryptElGamalByDll(inputBytes, key);
    });
}

void EncryptCaesarFileByStream(const CoreOptions& options) {
    CaesarKey key = ReadCaesarKeyFromFile(options.keyFilePath);
    ProcessFileByStream(options, OpenTextChunkSize, [&](const vector<uint8_t>& inputBytes) {
        return EncryptCaesarByDll(inputBytes, key);
    });
}

void DecryptCaesarFileByStream(const CoreOptions& options) {
    CaesarKey key = ReadCaesarKeyFromFile(options.keyFilePath);
    ProcessFileByStream(options, OpenTextChunkSize, [&](const vector<uint8_t>& inputBytes) {
        return DecryptCaesarByDll(inputBytes, key);
    });
}

void EncryptChaCha20FileByStream(const CoreOptions& options) {
    ChaCha20Key key = ReadChaCha20KeyFromFile(options.keyFilePath);
    uint32_t currentCounter = key.counter;
    ProcessFileByStream(options, OpenTextChunkSize, [&](const vector<uint8_t>& inputBytes) {
        ChaCha20Key chunkKey = key;
        chunkKey.counter = currentCounter;
        vector<uint8_t> outputBytes = EncryptChaCha20ByDll(inputBytes, chunkKey);
        currentCounter = CalculateNextChaCha20Counter(currentCounter, inputBytes.size());
        return outputBytes;
    });
}

void DecryptChaCha20FileByStream(const CoreOptions& options) {
    ChaCha20Key key = ReadChaCha20KeyFromFile(options.keyFilePath);
    uint32_t currentCounter = key.counter;
    ProcessFileByStream(options, OpenTextChunkSize, [&](const vector<uint8_t>& inputBytes) {
        ChaCha20Key chunkKey = key;
        chunkKey.counter = currentCounter;
        vector<uint8_t> outputBytes = DecryptChaCha20ByDll(inputBytes, chunkKey);
        currentCounter = CalculateNextChaCha20Counter(currentCounter, inputBytes.size());
        return outputBytes;
    });
}
