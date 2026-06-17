#include "ConvertUtils.h"

vector<uint8_t> NumbersToBinary(const vector<uint64_t>& numbers) {
    vector<uint8_t> bytes;
    vector<int> shifts = {0, 8, 16, 24, 32, 40, 48, 56};
    bytes.reserve(numbers.size() * sizeof(uint64_t));
    for (uint64_t number : numbers) {
        uint64_t value = number;
        for (int shift : shifts) {
            uint8_t byte = (value >> shift) & 255;
            bytes.push_back(byte);
        }
    }
    return bytes;
}
