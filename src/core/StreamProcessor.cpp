#include "StreamProcessor.h"
#include "FileProcessor.h"
#include "../../libs/algorithms/ElGamal/ElGamal.hpp"
#include "../../libs/algorithms/Rsa/Rsa.h"
#include "../../libs/algorithms/Shamir/Shamir.h"
#include "../../libs/helpers/ElGamalBlockConverter/ElGamalBlockConverter.h"
#include "../../libs/helpers/KeyFile/KeyFile.h"
#include <fstream>
#include <stdexcept>

const size_t OpenTextChunkSize = 4096;
const size_t CipherTextChunkSize = OpenTextChunkSize * sizeof(int64_t);
const size_t ElGamalCipherTextChunkSize = OpenTextChunkSize * ElGamalBlockSize;

void EncryptRsaFileByStream(const CoreOptions& options) {
    RsaKey key = ReadRsaKeyFromFile(options.keyFilePath);
    ifstream inputFile(options.inputFilePath, ios::binary);
    ofstream outputFile(options.outputFilePath, ios::binary);
    if (!inputFile || !outputFile) {
        throw runtime_error("Не удалось открыть файл");
    }
    vector<uint8_t> inputBytes = ReadBinaryChunk(inputFile, OpenTextChunkSize);
    while (!inputBytes.empty()) {
        vector<uint8_t> outputBytes = EncryptRsa(inputBytes, key.publicKey, key.moduleValue);
        WriteBinaryChunk(outputFile, outputBytes);
        inputBytes = ReadBinaryChunk(inputFile, OpenTextChunkSize);
    }
}

void DecryptRsaFileByStream(const CoreOptions& options) {
    RsaKey key = ReadRsaKeyFromFile(options.keyFilePath);
    ifstream inputFile(options.inputFilePath, ios::binary);
    ofstream outputFile(options.outputFilePath, ios::binary);
    if (!inputFile || !outputFile) {
        throw runtime_error("Не удалось открыть файл");
    }
    vector<uint8_t> inputBytes = ReadBinaryChunk(inputFile, CipherTextChunkSize);
    while (!inputBytes.empty()) {
        vector<uint8_t> outputBytes = DecryptRsa(inputBytes, key.privateKey, key.moduleValue);
        WriteBinaryChunk(outputFile, outputBytes);
        inputBytes = ReadBinaryChunk(inputFile, CipherTextChunkSize);
    }
}

void EncryptShamirFileByStream(const CoreOptions& options) {
    ShamirKey key = ReadShamirKeyFromFile(options.keyFilePath);
    ifstream inputFile(options.inputFilePath, ios::binary);
    ofstream outputFile(options.outputFilePath, ios::binary);
    if (!inputFile || !outputFile) {
        throw runtime_error("Не удалось открыть файл");
    }
    vector<uint8_t> inputBytes = ReadBinaryChunk(inputFile, OpenTextChunkSize);
    while (!inputBytes.empty()) {
        vector<uint8_t> outputBytes = EncryptShamir(inputBytes, key.primeValue, key.caValue, key.cbValue);
        WriteBinaryChunk(outputFile, outputBytes);
        inputBytes = ReadBinaryChunk(inputFile, OpenTextChunkSize);
    }
}

void DecryptShamirFileByStream(const CoreOptions& options) {
    ShamirKey key = ReadShamirKeyFromFile(options.keyFilePath);
    ifstream inputFile(options.inputFilePath, ios::binary);
    ofstream outputFile(options.outputFilePath, ios::binary);
    if (!inputFile || !outputFile) {
        throw runtime_error("Не удалось открыть файл");
    }
    vector<uint8_t> inputBytes = ReadBinaryChunk(inputFile, CipherTextChunkSize);
    while (!inputBytes.empty()) {
        vector<uint8_t> outputBytes = DecryptShamir(inputBytes, key.primeValue, key.daValue, key.dbValue);
        WriteBinaryChunk(outputFile, outputBytes);
        inputBytes = ReadBinaryChunk(inputFile, CipherTextChunkSize);
    }
}

void EncryptElGamalFileByStream(const CoreOptions& options) {
    ElGamalKey key = ReadElGamalKeyFromFile(options.keyFilePath);
    ifstream inputFile(options.inputFilePath, ios::binary);
    ofstream outputFile(options.outputFilePath, ios::binary);
    if (!inputFile || !outputFile) {
        throw runtime_error("Не удалось открыть файл");
    }
    vector<uint8_t> inputBytes = ReadBinaryChunk(inputFile, OpenTextChunkSize);
    while (!inputBytes.empty()) {
        vector<EncryptedBlockElGamal> encryptedBlocks =
            EncryptBytesElGamal(inputBytes, key.publicKey, key.primeModulus, key.generatorValue);
        vector<uint8_t> outputBytes = ElGamalBlocksToBytes(encryptedBlocks);
        WriteBinaryChunk(outputFile, outputBytes);
        inputBytes = ReadBinaryChunk(inputFile, OpenTextChunkSize);
    }
}

void DecryptElGamalFileByStream(const CoreOptions& options) {
    ElGamalKey key = ReadElGamalKeyFromFile(options.keyFilePath);
    ifstream inputFile(options.inputFilePath, ios::binary);
    ofstream outputFile(options.outputFilePath, ios::binary);
    if (!inputFile || !outputFile) {
        throw runtime_error("Не удалось открыть файл");
    }
    vector<uint8_t> inputBytes = ReadBinaryChunk(inputFile, ElGamalCipherTextChunkSize);
    while (!inputBytes.empty()) {
        vector<EncryptedBlockElGamal> encryptedBlocks = BytesToElGamalBlocks(inputBytes);
        vector<uint8_t> outputBytes = DecryptBytesElGamal(encryptedBlocks, key.privateKey, key.primeModulus);
        WriteBinaryChunk(outputFile, outputBytes);
        inputBytes = ReadBinaryChunk(inputFile, ElGamalCipherTextChunkSize);
    }
}
