#include "TestDll/TestDll.h"

#include <iostream>

using namespace std;

int main() {
    cout << "==========================================\n";
    cout << "      EncryptDecryptApp — DLL тесты       \n";
    cout << "==========================================\n";

    RunDllTests();

    cout << "\n==========================================\n";
    cout << "       Все DLL тесты пройдены.            \n";
    cout << "==========================================\n";
    return 0;
}