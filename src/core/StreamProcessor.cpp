#include "StreamProcessor.h"
#include "DllProcessor.h"
#include "FileProcessor.h"
#include "../../libs/helpers/ElGamalBlockConverter/ElGamalBlockConverter.h"
#include "../../libs/helpers/KeyFile/KeyFile.h"
#include <fstream>
#include <functional>
#include <stdexcept>

const size_t OpenTextChunkSize = 4096;
const size_t CipherTextChunkSize = OpenTextChunkSize * sizeof(uint64_t);
const size_t ElGamalCipherTextChunkSize = OpenTextChunkSize * ElGamalBlockSize;

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
