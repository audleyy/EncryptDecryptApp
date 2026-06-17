CXX = g++
CXXFLAGS = -Wall -Wextra -Werror

SRCS = test/test.cpp libs/algorithms/DiffieHellman/DiffieHellman.cpp libs/algorithms/ElGamal/ElGamal.cpp libs/algorithms/ElGamal/ElGamalDll.cpp
TARGET = run_tests

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(TARGET)