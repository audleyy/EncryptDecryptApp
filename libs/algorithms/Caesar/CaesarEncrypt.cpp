
#include "CaesarEncrypt.h"

using namespace std;

vector<uint8_t> EncryptCaesar( const std::vector<uint8_t>& input, uint64_t shift) {
    vector<uint8_t> output(input.size());
    shift = shift % CaesarAlphabetSize;
    for (size_t i = 0; i < input.size(); i++) {
        output[i] = (input[i] + shift) % CaesarAlphabetSize;
    }
    return output;
}
