CXX = c++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror

BIN_DIR = bin

TEST_APP = $(BIN_DIR)/test_crypto
DLL_TEST_APP = $(BIN_DIR)/test_dll
RSA_LIB = $(BIN_DIR)/librsa.dylib
SHAMIR_LIB = $(BIN_DIR)/libshamir.dylib

MATH_SRC = \
	libs/algorithms/MathCrypto/mod.cpp \
	libs/algorithms/MathCrypto/prime.cpp \
	libs/algorithms/MathCrypto/euclid.cpp

HELPERS_SRC = \
	libs/helpers/BytesToNumbers.cpp \
	libs/helpers/NumbersToBytes.cpp \
	libs/helpers/NumbersToBinary.cpp \
	libs/helpers/BinaryToNumbers.cpp \
	libs/helpers/KeyFile/RsaKeyFile.cpp \
	libs/helpers/KeyFile/ShamirKeyFile.cpp

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

TEST_SRC = \
	TestMain.cpp \
	TestUtils/TestUtils.cpp \
	TestRsa/TestRsa.cpp \
	TestShamir/TestShamir.cpp

DLL_TEST_SRC = \
	TestDllMain.cpp \
	TestUtils/TestUtils.cpp \
	TestDll/TestDll.cpp \
	TestDll/TestRsaDll.cpp \
	TestDll/TestShamirDll.cpp

all: test rsa shamir

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

test: $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_SRC) $(RSA_SRC) $(RSA_KEYGEN_SRC) $(SHAMIR_SRC) $(SHAMIR_KEYGEN_SRC) $(HELPERS_SRC) $(MATH_SRC) -o $(TEST_APP)
	./$(TEST_APP)

dll-test: rsa shamir
	$(CXX) $(CXXFLAGS) $(DLL_TEST_SRC) $(RSA_KEYGEN_SRC) $(SHAMIR_KEYGEN_SRC) $(MATH_SRC) -o $(DLL_TEST_APP)
	./$(DLL_TEST_APP)

rsa: $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -dynamiclib libs/algorithms/Rsa/RsaDll.cpp $(RSA_SRC) $(HELPERS_SRC) libs/algorithms/MathCrypto/mod.cpp -o $(RSA_LIB)

shamir: $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -dynamiclib libs/algorithms/Shamir/ShamirDll.cpp $(SHAMIR_SRC) $(HELPERS_SRC) libs/algorithms/MathCrypto/mod.cpp -o $(SHAMIR_LIB)

clean:
	rm -rf $(BIN_DIR)
