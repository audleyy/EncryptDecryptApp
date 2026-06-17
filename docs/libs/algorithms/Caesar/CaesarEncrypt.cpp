#include "CaesarEncrypt.h"

using namespace std;

vector<uint8_t> CaesarEncrypt(const vector<uint8_t>& input,const CaesarKey& key)
{
    vector<uint8_t> output(input.size());
    int shift = ((key.shift % CAESAR_ALPHABET_SIZE) + CAESAR_ALPHABET_SIZE) % CAESAR_ALPHABET_SIZE;

    for (size_t i = 0; i < input.size(); i++) {
        output[i] = (uint8_t)(
            (input[i] + shift) % CAESAR_ALPHABET_SIZE
        );
    }
    return output;
}