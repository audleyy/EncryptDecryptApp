#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<uint8_t> ReadBinaryFile(const string& filePath);
void WriteBinaryFile(const string& filePath, const vector<uint8_t>& bytes);
vector<uint8_t> ReadBinaryChunk(ifstream& file, size_t chunkSize);
void WriteBinaryChunk(ofstream& file, const vector<uint8_t>& bytes);

#endif
