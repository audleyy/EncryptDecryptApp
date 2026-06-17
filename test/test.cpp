#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <cstring>

#include "../libs/algorithms/DiffieHellman/DiffieHellman.hpp"
#include "../libs/algorithms/ElGamal/ElGamal.hpp"

extern "C" {
	int encrypt(const uint8_t*, size_t, uint64_t, uint64_t, uint64_t, uint8_t*, size_t, size_t*);
	int decrypt(const uint8_t*, size_t, uint64_t, uint64_t, uint8_t*, size_t, size_t*);
}

static int passed = 0;
static int failed = 0;

#define RUN_TEST(fn) do { \
	try { fn(); passed++; } \
	catch (...) { failed++; } \
} while(0)

void test_modular_exp_and_shared_secret() {
	assert(CalculateModularExponentiation(2, 10, 1000) == 24);

	assert(CalculateModularExponentiation(7, 0, 13) == 1);

	bool threw = false;
	try { CalculateModularExponentiation(2, 3, 0); }
	catch (const std::invalid_argument&) { threw = true; }
	assert(threw);

	uint64_t p = 2147483647;
	uint64_t g = 16807;
	uint64_t a = GeneratePrivateKey(2, p - 2);
	uint64_t b = GeneratePrivateKey(2, p - 2);
	uint64_t A = GeneratePublicKey(g, a, p);
	uint64_t B = GeneratePublicKey(g, b, p);
	assert(GenerateSharedSecret(B, a, p) == GenerateSharedSecret(A, b, p));
}

void test_elgamal_bytes_roundtrip() {
	uint64_t p = 2147483647;
	uint64_t g = 16807;
	uint64_t priv = GeneratePrivateKey(2, p - 2);
	uint64_t pub  = GeneratePublicKey(g, priv, p);

	uint8_t original[] = "Hello, ElGamal!";
	size_t len = sizeof(original);

	vector<uint8_t> in(original, original + len);
	auto enc = EncryptBytesElGamal(in, pub, p, g);
	auto dec = DecryptBytesElGamal(enc, priv, p);

	assert(dec.size() == len);
	assert(memcmp(dec.data(), original, len) == 0);
}

void test_dll_api_roundtrip() {
	uint64_t p = 2147483647;
	uint64_t g = 16807;
	uint64_t priv = GeneratePrivateKey(2, p - 2);
	uint64_t pub  = GeneratePublicKey(g, priv, p);

	uint8_t msg[] = { 0xDE, 0xAD, 0xBE, 0xEF };
	size_t msgLen = sizeof(msg);
	size_t outSize = 0;

	encrypt(msg, msgLen, p, g, pub, nullptr, 0, &outSize);
	assert(outSize == msgLen * sizeof(EncryptedBlockElGamal));

	vector<uint8_t> encBuf(outSize);
	assert(encrypt(msg, msgLen, p, g, pub, encBuf.data(), outSize, &outSize) == 0);

	size_t decSize = 0;
	decrypt(encBuf.data(), outSize, p, priv, nullptr, 0, &decSize);
	assert(decSize == msgLen);

	vector<uint8_t> decBuf(decSize);
	assert(decrypt(encBuf.data(), outSize, p, priv, decBuf.data(), decSize, &decSize) == 0);

	assert(memcmp(decBuf.data(), msg, msgLen) == 0);

	uint8_t bad[] = {1, 2, 3};
	size_t dummy = 0;
	assert(decrypt(bad, 3, p, priv, nullptr, 0, &dummy) == 1);
}

int main() {
	RUN_TEST(test_modular_exp_and_shared_secret);
	RUN_TEST(test_elgamal_bytes_roundtrip);
	RUN_TEST(test_dll_api_roundtrip);
	printf("\nResult: %d passed, %d failed\n", passed, failed);
	return failed ? 1 : 0;
}