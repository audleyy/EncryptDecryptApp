#include "TestCaesar.h"
#include "../TestUtils/TestUtils.h"
#include "../../docs/libs/algorithms/caesar/CaesarEncrypt.h"
#include "../../docs/libs/algorithms/caesar/CaesarDecrypt.h"

#include <cassert>
#include <iostream>
#include <vector>
#include <string>

using namespace std;



static void TestCaesarRoundTrip(
    const vector<uint8_t>& input,
    int shift,
    const string& testName)
{
    cout << "Проверяем: " << testName << "\n";
    vector<uint8_t> encrypted = EncryptCaesar(input, shift);
    vector<uint8_t> decrypted = DecryptCaesar(encrypted, shift);
    CheckTest(decrypted == input, testName);
    assert(decrypted == input);
}



void RunCaesarTests() {
    cout << "\n---Тесты Caesar ---\n";

   
    {
        string msg = "Hello, Caesar!";
        vector<uint8_t> input(msg.begin(), msg.end());
        TestCaesarRoundTrip(input, 3, "Caesar: базовый сдвиг 3");
    }

 
    {
        string msg = "No shift here";
        vector<uint8_t> input(msg.begin(), msg.end());
        TestCaesarRoundTrip(input, 0, "Caesar: нулевой сдвиг");
    }


    {
        string msg = "Big shift test";
        vector<uint8_t> input(msg.begin(), msg.end());
        TestCaesarRoundTrip(input, 200, "Caesar: большой сдвиг 200");
    }

   
    {
        string msg = "Negative shift";
        vector<uint8_t> input(msg.begin(), msg.end());
        TestCaesarRoundTrip(input, -5, "Caesar: отрицательный сдвиг -5");
    }

    
    {
        vector<uint8_t> input;
        vector<uint8_t> encrypted = EncryptCaesar(input, 10);
        cout << "Проверяем: Caesar: пустые данные\n";
        CheckTest(encrypted.empty(), "Caesar: пустые данные");
        assert(encrypted.empty());
    }


    {
        string msg = "Different output";
        vector<uint8_t> input(msg.begin(), msg.end());
        vector<uint8_t> encrypted = EncryptCaesar(input, 13);
        cout << "Проверяем: Caesar: шифртекст отличается\n";
        CheckTest(input != encrypted, "Caesar: шифртекст отличается");
        assert(input != encrypted);
    }

  
    {
        string msg = "Wrap around";
        vector<uint8_t> input(msg.begin(), msg.end());
        vector<uint8_t> enc256 = EncryptCaesar(input, 256);
        cout << "Проверяем: Caesar: цикличность 256\n";
        CheckTest(enc256 == input, "Caesar: цикличность 256");
        assert(enc256 == input);
    }

    cout << "=== Caesar: все тесты пройдены ===\n";
}