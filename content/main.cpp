#include <iostream>
#include "Algorithms/DFM/DFM.h"
#include "Algorithms/BRID/BRID.h"
#include "Algorithms/MMR/MMR.h"
#include "Algorithms/Motley/Motley.h"
#include "Algorithms/Swap/Swap.h"
#include "DataStructures/Data/Data.h"

// Main de pruebas. puede ser descartado
int main() {
    
    auto fn1 = [](const Data<int>& a, const Data<int>& b) {
        return static_cast<float>(a.getContent() + b.getContent()); //should be embeding
    };

    DFM<int> xd(fn1, fn1);

    printf("hello world\n");
    return 0;
}