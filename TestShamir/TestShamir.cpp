#include "TestShamir.h"
#include "../TestUtils/TestUtils.h"
#include "../libs/algorithms/Shamir/Shamir.h"
#include "../libs/algorithms/ShamirKeygen/ShamirKeygen.h"
#include <cstdint>
#include <string>
#include <vector>

using namespace std;

void TestShamirRoundTrip(const vector<uint8_t>& inputBytes, const ShamirKey& key, const string& testName) {
    vector<uint8_t> encryptedBytes = EncryptShamir(inputBytes, key.primeValue, key.caValue, key.cbValue);
    vector<uint8_t> decryptedBytes = DecryptShamir(encryptedBytes, key.primeValue, key.daValue, key.dbValue);

    CheckTest(decryptedBytes == inputBytes, testName);
}

void RunShamirTests() {
    TestShamirRoundTrip({0, 1, 2, 255}, GenerateShamirKey(257, 3, 5), "Shamir small bytes");
    TestShamirRoundTrip({72, 101, 108, 108, 111}, GenerateShamirKey(263, 5, 7), "Shamir text bytes");
    TestShamirRoundTrip({10, 20, 30, 40, 250}, GenerateRandomShamirKey(257, 313), "Shamir random key");
}
