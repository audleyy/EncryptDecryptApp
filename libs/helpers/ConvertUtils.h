#ifndef CONVERT_UTILS_H
#define CONVERT_UTILS_H

#include <cstdint>
#include <stdexcept>
#include <vector>

using namespace std;

vector<int64_t> BytesToNumbers(const vector<uint8_t>& bytes);
vector<uint8_t> NumbersToBytes(const vector<int64_t>& numbers);
vector<uint8_t> NumbersToBinary(const vector<int64_t>& numbers);
vector<int64_t> BinaryToNumbers(const vector<uint8_t>& bytes);
vector<int64_t> ProcessNumbers(const vector<int64_t>& numbers, int64_t power, int64_t modulo);

#endif
