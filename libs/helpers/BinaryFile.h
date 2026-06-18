#ifndef BINARY_FILE_H
#define BINARY_FILE_H

#include <fstream>
#include <stdexcept>
#include <cstdint>
#include <string>
#include <vector>

using namespace std;

vector<uint8_t> ReadBinaryFile(const string& filePath);
void WriteBinaryFile(const string& filePath, const vector<uint8_t>& bytes);

#endif
