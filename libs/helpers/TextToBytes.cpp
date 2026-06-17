#include "ConvertUtils.h"

vector<uint8_t> TextToBytes(const string& text) {
    vector<uint8_t> bytes;
    bytes.reserve(text.size());
    for (char symbol : text) {
        bytes.push_back(symbol);
    }
    return bytes;
}

string BytesToText(const vector<uint8_t>& bytes) {
    string text;
    text.reserve(bytes.size());
    for (uint8_t byte : bytes) {
        text.push_back(byte);
    }
    return text;
}
