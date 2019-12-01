#include <iostream>
#include <vector>
#include "Strategy/Strategy.h"
#include "Simplex.h"



using namespace std;



int main() {

    vector<vector<double>> strategy_a1;
    strategy_a1.push_back({{ 6, 18,  6, 15}});
    strategy_a1.push_back({{17,  8, 13, 14}});
    strategy_a1.push_back({{16, 16, 18, 2}});
    strategy_a1.push_back({{18,  8,  4, 18}});
    strategy_a1.push_back({{15,  8,  3, 19}});

    Strategy A(strategy_a1);
    A.print();
    auto M = A.getMatrixForB();
    Simplex K(M, false,8,18);
    K.print();
    K.printMatrix();
    K.printMatrixWithVariables();
    K.Solve();

    return 0;
}