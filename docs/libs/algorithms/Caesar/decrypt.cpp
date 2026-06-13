#include "caesar.h"

vector<uint8_t> DecryptCaesar(const vector<uint8_t>& input, int shift) {
    return EncryptCaesar(input, -shift);
}

string DecryptCaesarString(const string& text, int shift) {
    vector<uint8_t> input(text.begin(), text.end());
    vector<uint8_t> output = DecryptCaesar(input, shift);
    return string(output.begin(), output.end());
}