#pragma once
#include <cstdint>
#include <cstddef>
#include <vector>
#include <stdexcept>
#include <string>

using namespace std;

constexpr size_t CHACHA20_KEY_SIZE = 32;
constexpr size_t CHACHA20_NONCE_SIZE = 12;
constexpr size_t CHACHA20_BLOCK_SIZE = 64;
constexpr uint32_t CHACHA20_MAX_COUNTER = 0xFFFFFFFFu;
using ByteVec = std::vector<uint8_t>;