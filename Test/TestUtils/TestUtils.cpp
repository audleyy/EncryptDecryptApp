#include "TestUtils.h"
#include <cassert>
#include <iostream>

using namespace std;

void CheckTest(bool condition, const string& testName) {
    if (condition)
        cout << "  [ OK  ] " << testName << "\n";
    else
        cout << "  [FAIL] " << testName << "\n";
    assert(condition);
}