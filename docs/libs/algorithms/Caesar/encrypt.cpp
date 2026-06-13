
#include "caesar.h"


vector<uint8_t> EncryptCaesar(const vector<uint8_t>& input, int shift) {
    int effective_shift = ((shift % 26) + 26) % 26;
    vector<uint8_t> output;
    output.reserve(input.size());
    
    for (uint8_t c : input) {
        if (c >= 'A' && c <= 'Z')
            c = ((c - 'A' + effective_shift) % 26) + 'A';
        else if (c >= 'a' && c <= 'z')
            c = ((c - 'a' + effective_shift) % 26) + 'a';
        output.push_back(c);
    }
    return output;
}

string EncryptCaesarString(const string& text, int shift) {
    vector<uint8_t> input(text.begin(), text.end());
    vector<uint8_t> output = EncryptCaesar(input, shift);
    return string(output.begin(), output.end());
}