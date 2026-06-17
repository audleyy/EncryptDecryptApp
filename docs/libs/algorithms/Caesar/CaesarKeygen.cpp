#include "CaesarKeygen.h"

#include <cstdlib>
#include <ctime>

using namespace std;

CaesarKey CaesarGenerateKey() {
    static bool seeded = false;
    if (!seeded) {
        srand((unsigned int)time(nullptr));
        seeded = true;
    }
    return CaesarKey{ 1 + rand() % (CAESAR_ALPHABET_SIZE - 1) };
}