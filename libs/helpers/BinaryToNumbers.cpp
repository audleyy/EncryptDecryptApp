#include "ConvertUtils.h"

vector<uint64_t> BinaryToNumbers(const vector<uint8_t>& bytes) {
    vector<uint64_t> numbers;
    if (bytes.size() % sizeof(uint64_t) != 0) {
        throw runtime_error("Размер шифротекста некорректен");
    }
    uint64_t value = 0;
    int shift = 0;
    for (uint8_t byte : bytes) {
        uint64_t part = byte;
        value |= part << shift;
        shift += 8;
        if (shift == 64) {
            uint64_t number = value;
            numbers.push_back(number);
            value = 0;
            shift = 0;
        }
    }
    return numbers;
}
