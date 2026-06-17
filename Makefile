CXX = c++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror

BIN_DIR = bin

APP = $(BIN_DIR)/app
RSA_LIB = $(BIN_DIR)/librsa.dylib
SHAMIR_LIB = $(BIN_DIR)/libshamir.dylib
ELGAMAL_LIB = $(BIN_DIR)/libelgamal.dylib

MATH_SRC = \
	libs/algorithms/MathCrypto/mod.cpp \
	libs/algorithms/MathCrypto/prime.cpp \
	libs/algorithms/MathCrypto/euclid.cpp \
	libs/algorithms/MathCrypto/random.cpp

HELPERS_SRC = \
	libs/helpers/BytesToNumbers.cpp \
	libs/helpers/NumbersToBytes.cpp \
	libs/helpers/NumbersToBinary.cpp \
	libs/helpers/BinaryToNumbers.cpp \
	libs/helpers/TextToBytes.cpp \
	libs/helpers/HexConverter.cpp \
	libs/helpers/KeyFile/KeyNumbersFile.cpp \
	libs/helpers/KeyFile/RsaKeyFile.cpp \
	libs/helpers/KeyFile/ShamirKeyFile.cpp \
	libs/helpers/KeyFile/ElGamalKeyFile.cpp \
	libs/helpers/ElGamalBlockConverter/ElGamalBlockConverter.cpp

RSA_SRC = \
	libs/algorithms/Rsa/encrypt.cpp \
	libs/algorithms/Rsa/decrypt.cpp

RSA_KEYGEN_SRC = \
	libs/algorithms/RsaKeygen/RsaKeygen.cpp \
	libs/algorithms/RsaKeygen/RsaRandomKeygen.cpp

SHAMIR_SRC = \
	libs/algorithms/Shamir/encrypt.cpp \
	libs/algorithms/Shamir/decrypt.cpp

SHAMIR_KEYGEN_SRC = \
	libs/algorithms/ShamirKeygen/ShamirKeygen.cpp \
	libs/algorithms/ShamirKeygen/ShamirRandomKeygen.cpp

DIFFIE_HELLMAN_SRC = \
	libs/algorithms/DiffieHellman/DiffieHellman.cpp

ELGAMAL_SRC = \
	libs/algorithms/ElGamal/ElGamal.cpp

ELGAMAL_KEYGEN_SRC = \
	libs/algorithms/ElGamalKeygen/ElGamalKeygen.cpp

COMMON_SRC = \
	src/common/ErrorText.cpp

CORE_SRC = \
	src/core/Core.cpp \
	src/core/DllProcessor.cpp \
	src/core/FileProcessor.cpp \
	src/core/StreamProcessor.cpp

UI_SRC = \
	src/UI/CliParser.cpp \
	src/UI/ConsoleUI.cpp

APP_SRC = \
	main.cpp \
	$(UI_SRC) \
	$(COMMON_SRC) \
	$(CORE_SRC) \
	$(HELPERS_SRC) \
	$(RSA_KEYGEN_SRC) \
	$(SHAMIR_KEYGEN_SRC) \
	$(ELGAMAL_KEYGEN_SRC) \
	$(DIFFIE_HELLMAN_SRC) \
	$(MATH_SRC)

all: app rsa shamir elgamal

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

app: $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(APP_SRC) -o $(APP)

rsa: $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -dynamiclib libs/algorithms/Rsa/RsaDll.cpp $(RSA_SRC) $(HELPERS_SRC) libs/algorithms/MathCrypto/mod.cpp -o $(RSA_LIB)

shamir: $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -dynamiclib libs/algorithms/Shamir/ShamirDll.cpp $(SHAMIR_SRC) $(HELPERS_SRC) libs/algorithms/MathCrypto/mod.cpp -o $(SHAMIR_LIB)

elgamal: $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -dynamiclib libs/algorithms/ElGamal/ElGamalDll.cpp $(ELGAMAL_SRC) $(DIFFIE_HELLMAN_SRC) -o $(ELGAMAL_LIB)

clean:
	rm -rf $(BIN_DIR)
