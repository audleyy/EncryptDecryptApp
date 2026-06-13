#ifndef CAESAR_H
#define CAESAR_H

#include <cstdint>
#include <vector>
#include <string>

using namespace std;

vector<uint8_t> EncryptCaesar(const vector<uint8_t>& input, int shift);
vector<uint8_t> DecryptCaesar(const vector<uint8_t>& input, int shift);
string EncryptCaesarString(const string& text, int shift);
string DecryptCaesarString(const string& text, int shift);

#endif