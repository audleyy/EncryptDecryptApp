#include "TestRsa.h"
#include "../../libs/algorithms/Rsa/Rsa.h"
#include "../../libs/algorithms/RsaKeygen/RsaKeygen.h"
#include "../../libs/helpers/KeyFile/KeyFile.h"
#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void TestRsaRoundTrip(const vector<uint8_t>& inputBytes, const RsaKey& key, const string& testName) {
    cout << "Проверяем: " << testName << "\n";
    vector<uint8_t> encryptedBytes = EncryptRsa(inputBytes, key.publicKey, key.moduleValue);
    vector<uint8_t> decryptedBytes = DecryptRsa(encryptedBytes, key.privateKey, key.moduleValue);
    assert(decryptedBytes == inputBytes);
}

void RunRsaTests() {
    TestRsaRoundTrip({0, 1, 2, 255}, GenerateRsaKey(17, 23, 3), "RSA: маленький набор байтов");
    TestRsaRoundTrip({72, 101, 108, 108, 111}, GenerateRsaKey(19, 23, 5), "RSA: байты текста");
    TestRsaRoundTrip({10, 20, 30, 40, 250}, GenerateRandomRsaKey(17, 61), "RSA: случайный ключ");
    RsaKey key = GenerateRsaKey(17, 23, 3);
    SaveRsaKeyToFile("/private/tmp/rsa_key.bin", key);
    RsaKey fileKey = ReadRsaKeyFromFile("/private/tmp/rsa_key.bin");
    cout << "Проверяем: RSA: файл ключа\n";
    assert(fileKey.moduleValue == key.moduleValue);
    assert(fileKey.publicKey == key.publicKey);
    assert(fileKey.privateKey == key.privateKey);
}
