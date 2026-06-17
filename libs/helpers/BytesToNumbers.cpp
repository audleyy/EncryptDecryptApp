#include "ConvertUtils.h"

vector<uint64_t> BytesToNumbers(const vector<uint8_t>& bytes) {
    vector<uint64_t> numbers;
    numbers.reserve(bytes.size());
    for (uint8_t byte : bytes) {
        numbers.push_back(byte);
    }
    return numbers;
}
