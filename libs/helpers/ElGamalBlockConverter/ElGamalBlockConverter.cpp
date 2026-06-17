#include "ElGamalBlockConverter.h"
#include <stdexcept>

void WriteUint64ToBytes(vector<uint8_t>& bytes, uint64_t value) {
    vector<int> shifts = {0, 8, 16, 24, 32, 40, 48, 56};
    for (int shift : shifts) {
        uint8_t byte = (value >> shift) & 255;
        bytes.push_back(byte);
    }
}

uint64_t ReadUint64FromBytes(const vector<uint8_t>& bytes, size_t startIndex) {
    uint64_t value = 0;
    int shift = 0;
    for (size_t index = startIndex; index < startIndex + sizeof(uint64_t); index++) {
        uint64_t part = bytes[index];
        value |= part << shift;
        shift += 8;
    }
    return value;
}

vector<uint8_t> ElGamalBlocksToBytes(const vector<EncryptedBlockElGamal>& blocks) {
    vector<uint8_t> bytes;
    bytes.reserve(blocks.size() * ElGamalBlockSize);
    for (EncryptedBlockElGamal block : blocks) {
        WriteUint64ToBytes(bytes, block.firstHalf);
        WriteUint64ToBytes(bytes, block.secondHalf);
    }
    return bytes;
}

vector<EncryptedBlockElGamal> BytesToElGamalBlocks(const vector<uint8_t>& bytes) {
    if (bytes.size() % ElGamalBlockSize != 0) {
        throw runtime_error("Размер шифротекста Эль-Гамаля некорректен");
    }
    vector<EncryptedBlockElGamal> blocks;
    blocks.reserve(bytes.size() / ElGamalBlockSize);
    for (size_t index = 0; index < bytes.size(); index += ElGamalBlockSize) {
        EncryptedBlockElGamal block;
        block.firstHalf = ReadUint64FromBytes(bytes, index);
        block.secondHalf = ReadUint64FromBytes(bytes, index + sizeof(uint64_t));
        blocks.push_back(block);
    }
    return blocks;
}
