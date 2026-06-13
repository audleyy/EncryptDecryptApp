#include "TestUtils.h"
#include <iostream>
#include <stdexcept>

void CheckTest(bool condition, const string& testName) {
    if (!condition) {
        throw runtime_error("Тест не пройден: " + testName);
    }
    cout << "Тест пройден: " << testName << "\n";
}
