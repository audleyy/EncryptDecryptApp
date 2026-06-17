CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I./docs/libs

# ─── Исходники библиотек ──────────────────────────────────────────────────────

CAESAR_SRC = \
    docs/libs/algorithms/caesar/CaesarEncrypt.cpp \
    docs/libs/algorithms/caesar/CaesarDecrypt.cpp

CAESAR_DLL_SRC = \
    $(CAESAR_SRC) \
    docs/libs/algorithms/caesar/CaesarDll.cpp

CHACHA20_SRC = \
    docs/libs/algorithms/chacha20/ChaCha20Core.cpp \
    docs/libs/algorithms/chacha20/ChaCha20Context.cpp \
    docs/libs/algorithms/chacha20/ChaCha20Encrypt.cpp \
    docs/libs/algorithms/chacha20/ChaCha20Decrypt.cpp

CHACHA20_DLL_SRC = \
    $(CHACHA20_SRC) \
    docs/libs/algorithms/chacha20/ChaCha20Dll.cpp

# ─── Исходники тестов ─────────────────────────────────────────────────────────

TEST_SRC = \
    Test/TestMain.cpp \
    Test/TestUtils/TestUtils.cpp \
    Test/TestCaesar/TestCaesar.cpp \
    Test/TestChaCha20/TestChaCha20.cpp

DLL_TEST_SRC = \
    Test/TestDllMain.cpp \
    Test/TestUtils/TestUtils.cpp \
    Test/TestDll/TestDll.cpp \
    Test/TestDll/TestCaesarDll.cpp \
    Test/TestDll/TestChaCha20Dll.cpp

# ─── Цели ─────────────────────────────────────────────────────────────────────

# Для macOS лучше использовать расширение .dylib вместо .so
all: libcaesar.dylib libchacha20.dylib test dll_test

# Сборка динамических библиотек
libcaesar.dylib:
	$(CXX) $(CXXFLAGS) -shared -fPIC \
		$(CAESAR_DLL_SRC)             \
		-o libcaesar.dylib

libchacha20.dylib:
	$(CXX) $(CXXFLAGS) -shared -fPIC \
		$(CHACHA20_DLL_SRC)           \
		-o libchacha20.dylib

# Unit тесты
test:
	$(CXX) $(CXXFLAGS)  \
		$(TEST_SRC)      \
		$(CAESAR_SRC)    \
		$(CHACHA20_SRC)  \
		-o test_runner
	./test_runner

# DLL тесты (.dylib используются как зависимости)
dll_test: libcaesar.dylib libchacha20.dylib
	$(CXX) $(CXXFLAGS)  \
		$(DLL_TEST_SRC)  \
		-ldl             \
		-o dll_test_runner
	./dll_test_runner

clean:
	rm -f test_runner dll_test_runner \
	      libcaesar.dylib libchacha20.dylib

.PHONY: all test dll_test clean
