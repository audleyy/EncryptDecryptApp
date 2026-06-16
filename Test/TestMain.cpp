#include "TestRsa/TestRsa.h"
#include "TestShamir/TestShamir.h"
#include <exception>
#include <iostream>

using namespace std;

int main() {
    try {
        RunRsaTests();
        RunShamirTests();
        cout << "Все тесты пройдены.\n";
        return 0;
    } catch (const exception& exceptionCaught) {
        cout << exceptionCaught.what() << "\n";
        return 1;
    }
}
