#include "TestDll.h"
#include "TestCaesarDLL.h"
#include "TestChaCha20Dll.h"
#include <iostream>
using namespace std;

void RunDllTests() {
    cout << "\n=== DLL тесты ===\n";
    RunCaesarDllTests();
    RunChaCha20DllTests();
    cout << "=== Все DLL тесты пройдены ===\n";
}