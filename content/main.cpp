#include <iostream>
using namespace std;

#include "Metric/DFM/DFM.h"
#include "DataStructures/Data/Data.h"

// Main de pruebas. puede ser descartado
int main() {
    /*
    auto fn = [](const int& a, const int& b) {
        return static_cast<float>(a + b);
    };
    */

    auto fn1 = [](const Data<int>& a, const Data<int>& b) {
        return static_cast<float>(a.getContent() + b.getContent()); //should be embeding
    };

    DFM<int> xd(fn1, fn1);

    printf("hello world\n");
    return 0;
}