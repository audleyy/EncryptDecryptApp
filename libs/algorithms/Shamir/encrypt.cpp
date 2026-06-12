#include "Shamir.h"
#include "../../helpers/ConvertUtils.h"
#include "../MathCrypto/CryptoUtils.h"

int64_t CalculateShamirX1(int64_t messageValue, int64_t caValue, int64_t primeValue){
    return modBinary(messageValue, caValue, primeValue);
}

int64_t CalculateShamirX2(int64_t x1Value, int64_t cbValue, int64_t primeValue){
    return modBinary(x1Value, cbValue, primeValue);
}

vector<uint8_t> EncryptShamir(const vector<uint8_t>& inputBytes, int64_t primeValue, int64_t caValue, int64_t cbValue){
    try {
        vector<int64_t> sourceNumbers = BytesToNumbers(inputBytes);
        vector<int64_t> encryptedNumbers;
        encryptedNumbers.reserve(sourceNumbers.size());
        for (size_t i = 0; i < sourceNumbers.size(); i++) {
            int64_t x1Value = CalculateShamirX1(sourceNumbers[i], caValue, primeValue);
            int64_t x2Value = CalculateShamirX2(x1Value, cbValue, primeValue);
            encryptedNumbers.push_back(x2Value);
        }
        
        return NumbersToBinary(encryptedNumbers);
    } catch (const exception& exceptionCaught) {
        throw runtime_error(string("Сбой при шифровании Шамира: ") + exceptionCaught.what());
    }
}
