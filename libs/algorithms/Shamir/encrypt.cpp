#include "Shamir.h"

uint64_t CalculateShamirX1(uint64_t messageValue, uint64_t caValue, uint64_t primeValue){
    return modBinary(messageValue, caValue, primeValue);
}

uint64_t CalculateShamirX2(uint64_t x1Value, uint64_t cbValue, uint64_t primeValue){
    return modBinary(x1Value, cbValue, primeValue);
}

vector<uint8_t> EncryptShamir(const vector<uint8_t>& inputBytes, uint64_t primeValue, uint64_t caValue, uint64_t cbValue){
    try {
        vector<uint64_t> sourceNumbers = BytesToNumbers(inputBytes);
        vector<uint64_t> encryptedNumbers;
        encryptedNumbers.reserve(sourceNumbers.size());
        for (size_t i = 0; i < sourceNumbers.size(); i++) {
            uint64_t x1Value = CalculateShamirX1(sourceNumbers[i], caValue, primeValue);
            uint64_t x2Value = CalculateShamirX2(x1Value, cbValue, primeValue);
            encryptedNumbers.push_back(x2Value);
        }
        
        return NumbersToBinary(encryptedNumbers);
    } catch (const exception& exceptionCaught) {
        throw runtime_error(string("Сбой при шифровании Шамира: ") + exceptionCaught.what());
    }
}
