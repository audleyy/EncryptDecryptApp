#include "ConvertUtils.h"

vector<uint8_t> NumbersToBytes(const vector<int64_t>& numbers) {
    vector<uint8_t> bytes;
    bytes.reserve(numbers.size());
    for (int64_t number : numbers) {
        if (number < 0 || number > 255) {
            throw runtime_error("Число не помещается в байт");
        }
        bytes.push_back(number);
    }
    return bytes;
}
