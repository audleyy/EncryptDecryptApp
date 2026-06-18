#include "ElGamal.h"

EncryptedBlockElGamal EncryptBlockElGamal(uint64_t messageValue, uint64_t bobPublicKey, uint64_t primeModulus, uint64_t generatorValue) {
	if (messageValue >= primeModulus) {
		throw invalid_argument("Ошибка: значение блока не может быть больше или равно модулю");
	}

	try {
		uint64_t sessionKey = GeneratePrivateKey(2, primeModulus - 2);

		uint64_t firstHalf = GeneratePublicKey(generatorValue, sessionKey, primeModulus);

		uint64_t sharedSecret = GenerateSharedSecret(bobPublicKey, sessionKey, primeModulus);

		uint64_t secondHalf = ((unsigned __int128)messageValue * sharedSecret) % primeModulus;

		EncryptedBlockElGamal resultBlock;
		resultBlock.firstHalf = firstHalf;
		resultBlock.secondHalf = secondHalf;
		return resultBlock;

	} catch (const exception& exceptionCaught) {
		throw runtime_error(string("Сбой при шифровании блока Эль-Гамаля: ") + exceptionCaught.what());
	}
}

uint64_t DecryptBlockElGamal(uint64_t firstHalf, uint64_t secondHalf, uint64_t bobPrivateKey, uint64_t primeModulus) {
	try {
		uint64_t sharedSecret = GenerateSharedSecret(firstHalf, bobPrivateKey, primeModulus);

		uint64_t inverseSecret = CalculateModularExponentiation(sharedSecret, primeModulus - 2, primeModulus);

		uint64_t decryptedMessage = ((unsigned __int128)secondHalf * inverseSecret) % primeModulus;

		return decryptedMessage;

	} catch (const exception& exceptionCaught) {
		throw runtime_error(string("Сбой при расшифровании блока Эль-Гамаля: ") + exceptionCaught.what());
	}
}

vector<EncryptedBlockElGamal> EncryptBytesElGamal(const vector<uint8_t>& inputData, uint64_t bobPublicKey, uint64_t primeModulus, uint64_t generatorValue) {
	vector<EncryptedBlockElGamal> encryptedResult;
	encryptedResult.reserve(inputData.size()); 

	for (size_t index = 0; index < inputData.size(); ++index) {
		EncryptedBlockElGamal block = EncryptBlockElGamal((uint64_t)inputData[index], bobPublicKey, primeModulus, generatorValue);
		encryptedResult.push_back(block);
	}

	return encryptedResult;
}

vector<uint8_t> DecryptBytesElGamal(const vector<EncryptedBlockElGamal>& encryptedData, uint64_t bobPrivateKey, uint64_t primeModulus) {
	vector<uint8_t> decryptedResult;
	decryptedResult.reserve(encryptedData.size());

	for (size_t index = 0; index < encryptedData.size(); ++index) {
		uint64_t decryptedValue = DecryptBlockElGamal(encryptedData[index].firstHalf, encryptedData[index].secondHalf, bobPrivateKey, primeModulus);
		
		decryptedResult.push_back((uint8_t)decryptedValue);
	}

	return decryptedResult;
}