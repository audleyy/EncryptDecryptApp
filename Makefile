CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -fPIC
LDFLAGS = -dynamiclib



CAESAR_SRC = docs/libs/algorithms/caesar/CaesarEncrypt.cpp \
             docs/libs/algorithms/caesar/CaesarDecrypt.cpp \
             docs/libs/algorithms/caesar/CaesarKeygen.cpp \
             docs/libs/algorithms/caesar/CaesarDll.cpp

CHACHA_SRC = docs/libs/algorithms/chacha20/ChaCha20Round.cpp \
             docs/libs/algorithms/chacha20/ChaCha20Context.cpp \
             docs/libs/algorithms/chacha20/ChaCha20Encrypt.cpp \
             docs/libs/algorithms/chacha20/ChaCha20Decrypt.cpp \
             docs/libs/algorithms/chacha20/ChaCha20Keygen.cpp \
             docs/libs/algorithms/chacha20/ChaCha20Dll.cpp


CAESAR_OUT = libcaesar.dylib
CHACHA_OUT = libchacha20.dylib

.PHONY: all caesar chacha clean

all: caesar chacha

caesar: $(CAESAR_OUT)

chacha: $(CHACHA_OUT)

$(CAESAR_OUT): $(CAESAR_SRC)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(CAESAR_SRC) -o $(CAESAR_OUT)

$(CHACHA_OUT): $(CHACHA_SRC)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(CHACHA_SRC) -o $(CHACHA_OUT)

clean:
	rm -f $(CAESAR_OUT) $(CHACHA_OUT)
