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
        return static_cast<double>(a.getContent() + b.getContent()); //should be embeding
    };

    DFM<int> dfm(fn1, fn1);
    BRID<int> brid(fn1, fn1);
    MMR<int> mmr(fn1, fn1);
    Motley<int> motley(fn1, fn1);
    Swap<int> _swap(fn1, fn1);
    
    printf("hello world\n");
    return 0;
}