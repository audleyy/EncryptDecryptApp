#include "TestShamir.h"
#include "../../libs/algorithms/Shamir/Shamir.h"
#include "../../libs/algorithms/ShamirKeygen/ShamirKeygen.h"
#include "../../libs/helpers/KeyFile/KeyFile.h"
#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void TestShamirRoundTrip(const vector<uint8_t>& inputBytes, const ShamirKey& key, const string& testName) {
    cout << "Проверяем: " << testName << "\n";
    vector<uint8_t> encryptedBytes = EncryptShamir(inputBytes, key.primeValue, key.caValue, key.cbValue);
    vector<uint8_t> decryptedBytes = DecryptShamir(encryptedBytes, key.primeValue, key.daValue, key.dbValue);
    assert(decryptedBytes == inputBytes);
}

void RunShamirTests() {
    TestShamirRoundTrip({0, 1, 2, 255}, GenerateShamirKey(257, 3, 5), "Шамир: маленький набор байтов");
    TestShamirRoundTrip({72, 101, 108, 108, 111}, GenerateShamirKey(263, 5, 7), "Шамир: байты текста");
    TestShamirRoundTrip({10, 20, 30, 40, 250}, GenerateRandomShamirKey(257, 313), "Шамир: случайный ключ");
    ShamirKey key = GenerateShamirKey(257, 3, 5);
    SaveShamirKeyToFile("/private/tmp/shamir_key.bin", key);
    ShamirKey fileKey = ReadShamirKeyFromFile("/private/tmp/shamir_key.bin");
    cout << "Проверяем: Шамир: файл ключа\n";
    assert(fileKey.primeValue == key.primeValue);
    assert(fileKey.caValue == key.caValue);
    assert(fileKey.cbValue == key.cbValue);
    assert(fileKey.daValue == key.daValue);
    assert(fileKey.dbValue == key.dbValue);
}
