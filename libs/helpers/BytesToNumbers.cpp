#include "ConvertUtils.h"

vector<int64_t> bytesToNumbers(const vector<uint8_t>& bytes) {
    vector<int64_t> numbers;
    numbers.reserve(bytes.size());
    for (uint8_t byte : bytes) {
        numbers.push_back(byte);
    }
    return numbers;
}
