#include "TestChaCha20.h"
#include "../TestUtils/TestUtils.h"
#include "algorithms/chacha20/ChaCha20Encrypt.h"
#include "algorithms/chacha20/ChaCha20Decrypt.h"
#include "algorithms/chacha20/ChaCha20Context.h"
#include "algorithms/chacha20/ChaCha20Core.h"

#include <cassert>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

// ─── Тестовые данные ─────────────────────────────────────────────────────────

static const uint8_t TEST_KEY[32] = {
    0x00,0x01,0x02,0x03, 0x04,0x05,0x06,0x07,
    0x08,0x09,0x0a,0x0b, 0x0c,0x0d,0x0e,0x0f,
    0x10,0x11,0x12,0x13, 0x14,0x15,0x16,0x17,
    0x18,0x19,0x1a,0x1b, 0x1c,0x1d,0x1e,0x1f
};

static const uint8_t TEST_NONCE[12] = {
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x4a,
    0x00,0x00,0x00,0x00
};

// ─── Вспомогательная функция ─────────────────────────────────────────────────

static void TestChaCha20RoundTrip(
    const vector<uint8_t>& input,
    const ByteVec& key,
    const ByteVec& nonce,
    uint32_t counter,
    const string& testName)
{
    cout << "Проверяем: " << testName << "\n";
    ByteVec encrypted = EncryptChaCha20(input, key, nonce, counter);
    ByteVec decrypted = DecryptChaCha20(encrypted, key, nonce, counter);
    CheckTest(decrypted == input, testName);
    assert(decrypted == input);
}

// ─── Тесты ───────────────────────────────────────────────────────────────────

void RunChaCha20Tests() {
    cout << "\n=== Тесты ChaCha20 ===\n";

    ByteVec key(TEST_KEY, TEST_KEY + 32);
    ByteVec nonce(TEST_NONCE, TEST_NONCE + 12);

    // Базовый тест
    {
        string msg = "Hello, ChaCha20!";
        ByteVec input(msg.begin(), msg.end());
        TestChaCha20RoundTrip(input, key, nonce, 1,
            "ChaCha20: базовый тест");
    }

    // Пустые данные
    {
        ByteVec input;
        ByteVec encrypted = EncryptChaCha20(input, key, nonce, 0);
        cout << "Проверяем: ChaCha20: пустые данные\n";
        CheckTest(encrypted.empty(), "ChaCha20: пустые данные");
        assert(encrypted.empty());
    }

    // Многоблочный тест (> 64 байт)
    {
        ByteVec input(200, 0xAB);
        TestChaCha20RoundTrip(input, key, nonce, 0,
            "ChaCha20: многоблочный тест");
    }

    // Шифртекст != открытый текст
    {
        string msg = "Different output test";
        ByteVec input(msg.begin(), msg.end());
        ByteVec encrypted = EncryptChaCha20(input, key, nonce, 0);
        cout << "Проверяем: ChaCha20: шифртекст отличается\n";
        CheckTest(input != encrypted, "ChaCha20: шифртекст отличается");
        assert(input != encrypted);
    }

    // Неверный ключ при дешифровании
    {
        string msg = "Wrong key test";
        ByteVec input(msg.begin(), msg.end());
        ByteVec wrongKey(32, 0xFF);
        ByteVec encrypted = EncryptChaCha20(input, key, nonce, 0);
        ByteVec decrypted = DecryptChaCha20(encrypted, wrongKey, nonce, 0);
        cout << "Проверяем: ChaCha20: неверный ключ\n";
        CheckTest(decrypted != input, "ChaCha20: неверный ключ");
        assert(decrypted != input);
    }

    // Неверный nonce при дешифровании
    {
        string msg = "Wrong nonce test";
        ByteVec input(msg.begin(), msg.end());
        ByteVec wrongNonce(12, 0xFF);
        ByteVec encrypted = EncryptChaCha20(input, key, nonce, 0);
        ByteVec decrypted = DecryptChaCha20(encrypted, key, wrongNonce, 0);
        cout << "Проверяем: ChaCha20: неверный nonce\n";
        CheckTest(decrypted != input, "ChaCha20: неверный nonce");
        assert(decrypted != input);
    }

    // Неверный счётчик при дешифровании
    {
        string msg = "Wrong counter test";
        ByteVec input(msg.begin(), msg.end());
        ByteVec encrypted = EncryptChaCha20(input, key, nonce, 0);
        ByteVec decrypted = DecryptChaCha20(encrypted, key, nonce, 1);
        cout << "Проверяем: ChaCha20: неверный счётчик\n";
        CheckTest(decrypted != input, "ChaCha20: неверный счётчик");
        assert(decrypted != input);
    }

    // Неверный размер ключа
    {
        ByteVec badKey(16, 0x00);
        ByteVec input = {0x01, 0x02};
        bool threw = false;
        try {
            EncryptChaCha20(input, badKey, nonce, 0);
        } catch (const std::invalid_argument&) {
            threw = true;
        }
        cout << "Проверяем: ChaCha20: неверный размер ключа\n";
        CheckTest(threw, "ChaCha20: неверный размер ключа");
        assert(threw);
    }

    // RFC 8439 тест-вектор
    {
        static const uint8_t rfc_key[32] = {
            0x00,0x01,0x02,0x03, 0x04,0x05,0x06,0x07,
            0x08,0x09,0x0a,0x0b, 0x0c,0x0d,0x0e,0x0f,
            0x10,0x11,0x12,0x13, 0x14,0x15,0x16,0x17,
            0x18,0x19,0x1a,0x1b, 0x1c,0x1d,0x1e,0x1f
        };
        static const uint8_t rfc_nonce[12] = {
            0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x4a,
            0x00,0x00,0x00,0x00
        };
        static const uint8_t expected[] = {
            0x6e,0x2e,0x35,0x9a, 0x25,0x68,0xf9,0x80,
            0x41,0xba,0x07,0x28, 0xdd,0x0d,0x69,0x81,
            0xe9,0x7e,0x7a,0xec, 0x1d,0x43,0x60,0xc2,
            0x0a,0x27,0xaf,0xcc, 0xfd,0x9f,0xae,0x0b,
            0xf9,0x1b,0x65,0xc5, 0x52,0x47,0x33,0xab,
            0x8f,0x59,0x3d,0xab, 0xcd,0x62,0xb3,0x57,
            0x16,0x39,0xd6,0x24, 0xe6,0x51,0x52,0xab,
            0x8f,0x53,0x0c,0x35, 0x9f,0x08,0x61,0xd8,
            0x07,0xca,0x0d,0xbf, 0x50,0x0d,0x6a,0x61,
            0x56,0xa3,0x8e,0x08, 0x8a,0x22,0xb6,0x5e,
            0x52,0xbc,0x51,0x4d, 0x16,0xcc,0xf8,0x06,
            0x81,0x8c,0xe9,0x1a, 0xb7,0x79,0x37,0x36,
            0x5a,0xf9,0x0b,0xbf, 0x74,0xa3,0x5b,0xe6,
            0xb4,0x0b,0x8e,0xed, 0xf2,0x78,0x5e,0x42,
            0x87,0x4d
        };

        const char* plaintext =
            "Ladies and Gentlemen of the class of '99: "
            "If I could offer you only one tip for the "
            "future, sunscreen would be it.";

        ByteVec rfcKey(rfc_key, rfc_key + 32);
        ByteVec rfcNonce(rfc_nonce, rfc_nonce + 12);
        ByteVec input((const uint8_t*)plaintext,
                      (const uint8_t*)plaintext + strlen(plaintext));

        ByteVec encrypted = EncryptChaCha20(input, rfcKey, rfcNonce, 1);

        cout << "Проверяем: ChaCha20: RFC 8439 тест-вектор\n";
        bool ok = (encrypted.size() == sizeof(expected)) &&
                  (memcmp(encrypted.data(), expected, sizeof(expected)) == 0);
        CheckTest(ok, "ChaCha20: RFC 8439 тест-вектор");
        assert(ok);
    }

    cout << "=== ChaCha20: все тесты пройдены ===\n";
}