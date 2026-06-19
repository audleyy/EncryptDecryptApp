CXX = c++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror
DEPFLAGS = -MMD -MP

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
LIB_EXT = .dylib
LIB_FLAGS = -dynamiclib -fPIC
else
LIB_EXT = .so
LIB_FLAGS = -shared -fPIC
endif

BIN_DIR = bin
BUILD_DIR = build
APP_OBJ_DIR = $(BUILD_DIR)/app

APP = $(BIN_DIR)/app
RSA_LIB = $(BIN_DIR)/librsa$(LIB_EXT)
SHAMIR_LIB = $(BIN_DIR)/libshamir$(LIB_EXT)
ELGAMAL_LIB = $(BIN_DIR)/libelgamal$(LIB_EXT)
CAESAR_LIB = $(BIN_DIR)/libcaesar$(LIB_EXT)
CHACHA20_LIB = $(BIN_DIR)/libchacha20$(LIB_EXT)

MATH_SRC = \
	libs/algorithms/MathCrypto/mod.cpp \
	libs/algorithms/MathCrypto/prime.cpp \
	libs/algorithms/MathCrypto/euclid.cpp \
	libs/algorithms/MathCrypto/random.cpp

CONVERT_SRC = \
	libs/helpers/BytesToNumbers.cpp \
	libs/helpers/NumbersToBytes.cpp \
	libs/helpers/NumbersToBinary.cpp \
	libs/helpers/BinaryToNumbers.cpp \
	libs/helpers/TextToBytes.cpp \
	libs/helpers/HexConverter.cpp

KEYFILE_SRC = \
	libs/helpers/KeyFile/KeyNumbersFile.cpp \
	libs/helpers/KeyFile/RsaKeyFile.cpp \
	libs/helpers/KeyFile/ShamirKeyFile.cpp \
	libs/helpers/KeyFile/ElGamalKeyFile.cpp \
	libs/helpers/KeyFile/CaesarKeyFile.cpp \
	libs/helpers/KeyFile/ChaCha20KeyFile.cpp

HELPERS_SRC = \
	$(CONVERT_SRC) \
	$(KEYFILE_SRC) \
	libs/helpers/BinaryFile.cpp \
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

CAESAR_SRC = \
	libs/algorithms/Caesar/CaesarEncrypt.cpp \
	libs/algorithms/Caesar/CaesarDecrypt.cpp

CAESAR_KEYGEN_SRC = \
	libs/algorithms/CaesarKeygen/CaesarKeygen.cpp

CHACHA20_SRC = \
	libs/algorithms/ChaCha20/ChaCha20Context.cpp \
	libs/algorithms/ChaCha20/ChaCha20Round.cpp \
	libs/algorithms/ChaCha20/ChaCha20Encrypt.cpp \
	libs/algorithms/ChaCha20/ChaCha20Decrypt.cpp

CHACHA20_KEYGEN_SRC = \
	libs/algorithms/ChaCha20Keygen/ChaCha20Keygen.cpp

COMMON_SRC = src/common/ErrorText.cpp

CORE_SRC = \
    src/core/Core.cpp \
    src/core/DllProcessor.cpp \
    src/core/FileProcessor.cpp \
    src/core/StreamProcessor.cpp

UI_SRC = \
    src/UI/CliParser.cpp \
    src/UI/ConsoleUI.cpp \
    src/UI/ManualPages.cpp

APP_SRC = \
	main.cpp \
	$(UI_SRC) \
	$(COMMON_SRC) \
	$(CORE_SRC) \
	$(HELPERS_SRC) \
	$(RSA_KEYGEN_SRC) \
	$(SHAMIR_KEYGEN_SRC) \
	$(ELGAMAL_KEYGEN_SRC) \
	$(CAESAR_KEYGEN_SRC) \
	$(CHACHA20_KEYGEN_SRC) \
	$(DIFFIE_HELLMAN_SRC) \
	$(MATH_SRC)

APP_OBJECTS = $(patsubst %.cpp,$(APP_OBJ_DIR)/%.o,$(APP_SRC))
APP_DEPS = $(APP_OBJECTS:.o=.d)

all: app rsa shamir elgamal caesar chacha20

prepare: $(BIN_DIR) $(APP_OBJECTS) rsa shamir elgamal caesar chacha20

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

app: $(APP)

$(APP): $(BIN_DIR) $(APP_OBJECTS)
	$(CXX) $(CXXFLAGS) $(APP_OBJECTS) -o $(APP)

$(APP_OBJ_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

rsa: $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LIB_FLAGS) libs/algorithms/Rsa/RsaDll.cpp $(RSA_SRC) $(CONVERT_SRC) libs/algorithms/MathCrypto/mod.cpp -o $(RSA_LIB)

shamir: $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LIB_FLAGS) libs/algorithms/Shamir/ShamirDll.cpp $(SHAMIR_SRC) $(CONVERT_SRC) libs/algorithms/MathCrypto/mod.cpp -o $(SHAMIR_LIB)

elgamal: $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LIB_FLAGS) libs/algorithms/ElGamal/ElGamalDll.cpp $(ELGAMAL_SRC) $(DIFFIE_HELLMAN_SRC) -o $(ELGAMAL_LIB)

caesar: $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LIB_FLAGS) libs/algorithms/Caesar/CaesarDll.cpp $(CAESAR_SRC) -o $(CAESAR_LIB)

chacha20: $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LIB_FLAGS) libs/algorithms/ChaCha20/ChaCha20Dll.cpp $(CHACHA20_SRC) -o $(CHACHA20_LIB)

clean:
	rm -rf $(BIN_DIR) $(BUILD_DIR)

clean-objects:
	rm -rf $(BUILD_DIR)

-include $(APP_DEPS)
