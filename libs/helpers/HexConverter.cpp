#include "ConvertUtils.h"

int HexDigitToValue(char symbol) {
    int value = -1;
    if (symbol >= '0' && symbol <= '9') {
        value = symbol - '0';
    } else if (symbol >= 'A' && symbol <= 'F') {
        value = symbol - 'A' + 10;
    } else if (symbol >= 'a' && symbol <= 'f') {
        value = symbol - 'a' + 10;
    }
    return value;
}

string BytesToHex(const vector<uint8_t>& bytes) {
    const string digits = "0123456789ABCDEF";
    string text;
    text.reserve(bytes.size() * 2);
    for (uint8_t byte : bytes) {
        text.push_back(digits[byte / 16]);
        text.push_back(digits[byte % 16]);
    }
    return text;
}

vector<uint8_t> HexToBytes(const string& text) {
    string preparedText;
    preparedText.reserve(text.size());
    for (char symbol : text) {
        bool isSpaceSymbol = symbol == ' ' || symbol == '\n' || symbol == '\r' || symbol == '\t';
        if (!isSpaceSymbol) {
            preparedText.push_back(symbol);
        }
    }

    if (preparedText.size() % 2 != 0) {
        throw invalid_argument("HEX-строка должна иметь четную длину");
    }

    vector<uint8_t> bytes;
    bytes.reserve(preparedText.size() / 2);
    for (size_t index = 0; index < preparedText.size(); index += 2) {
        int firstHalf = HexDigitToValue(preparedText[index]);
        int secondHalf = HexDigitToValue(preparedText[index + 1]);
        if (firstHalf < 0 || secondHalf < 0) {
            throw invalid_argument("HEX-строка содержит некорректный символ");
        }
        uint8_t byte = firstHalf * 16 + secondHalf;
        bytes.push_back(byte);
    }
    return bytes;
}
