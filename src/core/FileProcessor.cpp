#include "FileProcessor.h"

vector<uint8_t> ReadBinaryChunk(ifstream& file, size_t chunkSize) {
    vector<uint8_t> bytes;
    char symbol {};
    while (bytes.size() < chunkSize && file.get(symbol)) {
        bytes.push_back(symbol);
    }
    if (!file.good() && !file.eof()) {
        throw runtime_error("Не удалось прочитать файл");
    }
    return bytes;
}

void WriteBinaryChunk(ofstream& file, const vector<uint8_t>& bytes) {
    for (uint8_t byte : bytes) {
        file.put(byte);
    }
    if (!file) {
        throw runtime_error("Не удалось записать файл");
    }
}
