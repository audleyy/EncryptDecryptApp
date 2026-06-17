#ifndef CONVERT_UTILS_H
#define CONVERT_UTILS_H

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

vector<uint64_t> BytesToNumbers(const vector<uint8_t>& bytes);
vector<uint8_t> NumbersToBytes(const vector<uint64_t>& numbers);
vector<uint8_t> NumbersToBinary(const vector<uint64_t>& numbers);
vector<uint64_t> BinaryToNumbers(const vector<uint8_t>& bytes);
vector<uint8_t> TextToBytes(const string& text);
string BytesToText(const vector<uint8_t>& bytes);
string BytesToHex(const vector<uint8_t>& bytes);
vector<uint8_t> HexToBytes(const string& text);

#endif
