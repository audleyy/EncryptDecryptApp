#include "ElGamal.h"

extern "C" int encrypt(const uint8_t* inputData, size_t inputSize, uint64_t primeModulus, uint64_t generatorValue, uint64_t bobPublicKey, uint8_t* outputData, size_t outputCapacity, size_t* outputSize) {
	try {
		if (outputSize == nullptr || (inputData == nullptr && inputSize > 0)) {
			throw invalid_argument("Некорректные входные данные для протокола Эль-Гамаля");
		}

		vector<uint8_t> inputBytes(inputData, inputData + inputSize);
		
		vector<EncryptedBlockElGamal> resultBlocks = EncryptBytesElGamal(inputBytes, bobPublicKey, primeModulus, generatorValue);
		
		size_t requiredBytes = resultBlocks.size() * sizeof(EncryptedBlockElGamal);
		*outputSize = requiredBytes;

		if (outputData == nullptr || outputCapacity < requiredBytes) {
			throw length_error("Недостаточный размер выходного буфера для протокола Эль-Гамаля");
		}

		const uint8_t* rawData = (const uint8_t*)resultBlocks.data();
		copy(rawData, rawData + requiredBytes, outputData);

			return 0;
	} catch (const invalid_argument&) {
		return 1;
	} catch (const length_error&) {
		return 2;
	} catch (const exception&) {
		return 3;
	}
}

extern "C" int decrypt(const uint8_t* inputData, size_t inputSize, uint64_t primeModulus, uint64_t bobPrivateKey, uint8_t* outputData, size_t outputCapacity, size_t* outputSize) {
	try {
		if (outputSize == nullptr || (inputData == nullptr && inputSize > 0)) {
			throw invalid_argument("Некорректные входные данные для протокола Эль-Гамаля");
		}

		if (inputSize % sizeof(EncryptedBlockElGamal) != 0) {
			throw invalid_argument("Размер входных данных не кратен размеру блока Эль-Гамаля");
		}

		size_t blocksCount = inputSize / sizeof(EncryptedBlockElGamal);
		vector<EncryptedBlockElGamal> encryptedBlocks(blocksCount);
		
		const EncryptedBlockElGamal* rawInput = (const EncryptedBlockElGamal*)inputData;
		copy(rawInput, rawInput + blocksCount, encryptedBlocks.begin());

		vector<uint8_t> resultBytes = DecryptBytesElGamal(encryptedBlocks, bobPrivateKey, primeModulus);
		
		*outputSize = resultBytes.size();

		if (outputData == nullptr || outputCapacity < resultBytes.size()) {
			throw length_error("Недостаточный размер выходного буфера для протокола Эль-Гамаля");
		}

		copy(resultBytes.begin(), resultBytes.end(), outputData);

		return 0;
	} catch (const invalid_argument&) {
		return 1;
	} catch (const length_error&) {
		return 2;
	} catch (const exception&) {
		return 3;
	}
}