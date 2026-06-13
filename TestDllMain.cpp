#include "TestDll/TestDll.h"
#include <exception>
#include <iostream>

using namespace std;

int main() {
    try {
        RunDllTests();
        cout << "Все DLL-тесты пройдены.\n";
        return 0;
    } catch (const exception& exceptionCaught) {
        cout << exceptionCaught.what() << "\n";
        return 1;
    }
}
