#include "TestRsa.h"
#include "../TestUtils/TestUtils.h"
#include "../libs/algorithms/Rsa/Rsa.h"
#include "../libs/algorithms/RsaKeygen/RsaKeygen.h"
#include "../libs/helpers/KeyFile/KeyFile.h"
#include <cstdint>
#include <string>
#include <vector>

using namespace std;

void TestRsaRoundTrip(const vector<uint8_t>& inputBytes, const RsaKey& key, const string& testName) {
    vector<uint8_t> encryptedBytes = EncryptRsa(inputBytes, key.publicKey, key.moduleValue);
    vector<uint8_t> decryptedBytes = DecryptRsa(encryptedBytes, key.privateKey, key.moduleValue);
    CheckTest(decryptedBytes == inputBytes, testName);
}

void RunRsaTests() {
    TestRsaRoundTrip({0, 1, 2, 255}, GenerateRsaKey(17, 23, 3), "RSA: маленький набор байтов");
    TestRsaRoundTrip({72, 101, 108, 108, 111}, GenerateRsaKey(19, 23, 5), "RSA: байты текста");
    TestRsaRoundTrip({10, 20, 30, 40, 250}, GenerateRandomRsaKey(17, 61), "RSA: случайный ключ");
    RsaKey key = GenerateRsaKey(17, 23, 3);
    SaveRsaKeyToFile("/private/tmp/rsa_key.bin", key);
    RsaKey fileKey = ReadRsaKeyFromFile("/private/tmp/rsa_key.bin");
    CheckTest(fileKey.moduleValue == key.moduleValue && fileKey.publicKey == key.publicKey && fileKey.privateKey == key.privateKey, "RSA: файл ключа");
}
