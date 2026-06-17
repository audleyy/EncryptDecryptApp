#include "TestCaesar/TestCaesar.h"
#include "TestChaCha20/TestChaCha20.h"


#include <iostream>
using namespace std;

int main() {
    cout << "==========================================\n";
    cout << "      EncryptDecryptApp — Unit тесты      \n";
    cout << "==========================================\n";

    RunCaesarTests();
    RunChaCha20Tests();

    cout << "\n==========================================\n";
    cout << "       Все unit тесты пройдены!           \n";
    cout << "==========================================\n";
    return 0;
}