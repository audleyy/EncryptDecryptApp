#include "DiffieHellman.h"

uint64_t CalculateModularExponentiation(uint64_t baseValue, uint64_t exponentValue, uint64_t modulusValue) {
	if (modulusValue == 0) {
		throw invalid_argument("Ошибка: модуль не может быть равен нулю");
	}

	uint64_t resultValue = 1;
	baseValue = baseValue % modulusValue;

	while (exponentValue > 0) {
		if (exponentValue % 2 == 1) {
			resultValue = ((unsigned __int128)resultValue * baseValue) % modulusValue;
		}
		
		exponentValue = exponentValue >> 1;
		baseValue = ((unsigned __int128)baseValue * baseValue) % modulusValue;
	}

	return resultValue;
}

uint64_t GeneratePrivateKey(uint64_t minLimit, uint64_t maxLimit) {
	if (minLimit >= maxLimit) {
		throw invalid_argument("Ошибка: минимальный предел должен быть меньше максимального");
	}

	random_device hardwareRandomDevice;
	mt19937_64 randomEngine(hardwareRandomDevice());
	uniform_int_distribution<uint64_t> uniformDistribution(minLimit, maxLimit);

	return uniformDistribution(randomEngine);
}

uint64_t GeneratePublicKey(uint64_t generatorValue, uint64_t privateKey, uint64_t primeModulus) {
	try {
		return CalculateModularExponentiation(generatorValue, privateKey, primeModulus);
	} catch (const exception& exceptionCaught) {
		throw runtime_error(string("Сбой при генерации открытого ключа: ") + exceptionCaught.what());
	}
}

uint64_t GenerateSharedSecret(uint64_t otherPublicKey, uint64_t myPrivateKey, uint64_t primeModulus) {
	try {
		return CalculateModularExponentiation(otherPublicKey, myPrivateKey, primeModulus);
	} catch (const exception& exceptionCaught) {
		throw runtime_error(string("Сбой при вычислении общего секрета: ") + exceptionCaught.what());
	}
}