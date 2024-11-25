#include <iostream>
using namespace std;

#include "Algorithms/BRID/BRID.h"

// Main de pruebas. puede ser descartado
int main() {

    auto fn = [](const int& a, const int& b) {
        return static_cast<float>(a + b);
    };

    BRID<int> xd(fn, fn);

    printf("hello world\n");
    return 0;
}