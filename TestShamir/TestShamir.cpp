#include "TestShamir.h"
#include "../TestUtils/TestUtils.h"
#include "../libs/algorithms/Shamir/Shamir.h"
#include "../libs/algorithms/ShamirKeygen/ShamirKeygen.h"
#include "../libs/helpers/KeyFile/KeyFile.h"
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
    TestShamirRoundTrip({0, 1, 2, 255}, GenerateShamirKey(257, 3, 5), "Шамир: маленький набор байтов");
    TestShamirRoundTrip({72, 101, 108, 108, 111}, GenerateShamirKey(263, 5, 7), "Шамир: байты текста");
    TestShamirRoundTrip({10, 20, 30, 40, 250}, GenerateRandomShamirKey(257, 313), "Шамир: случайный ключ");
    ShamirKey key = GenerateShamirKey(257, 3, 5);
    SaveShamirKeyToFile("/private/tmp/shamir_key.bin", key);
    ShamirKey fileKey = ReadShamirKeyFromFile("/private/tmp/shamir_key.bin");
    CheckTest(fileKey.primeValue == key.primeValue && fileKey.caValue == key.caValue && fileKey.cbValue == key.cbValue && fileKey.daValue == key.daValue && fileKey.dbValue == key.dbValue, "Шамир: файл ключа");
}
