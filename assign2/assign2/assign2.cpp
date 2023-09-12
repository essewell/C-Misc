/******************************************************************************
;@ Student Name 1: Emmett Sewell    
;@ Student 1 #: 301565227
;@ Student 1 userid (email): esa97@sfu.ca
;@
;@ Student Name 2: Jaiden Nadem
;@ Student 2 #: 301562466
;@ Student 2 userid (email): jon1@sfu.ca
;@
;@ Helpers: none
;@
;@ Resources: none
;@
;@ Name: assign2.cpp
******************************************************************************/

#include <iostream>
#include <chrono>
#include "bignumber.h"
#include "templates.hpp"

using namespace std;
using namespace std::chrono;

int main() {
    cout << "Do not change this line.  Enter a sequence of increasing Fibonacci indicies and -1 to stop input." << endl;
    int n{-2};
    long long index{0};
    while (cin >> n, -1 != n) {
        long long prev = 0;
        index = n;
        cout << index << endl;
        if (n <= 92) {
            cout << fibonacci<long long>(index, prev) << endl;
        }
        else {
            BigNumber Index = index;
            BigNumber Previous = prev;
            cout << fibonacci<BigNumber>(Index, Previous) << endl;
        }
    }
    index = 0;
    long long previous = 0;
    const int runLimit{2};
    BigNumber Index = index;
    BigNumber Previous = previous;
    time_point<steady_clock> start = steady_clock::now();
    while ((steady_clock::now() - start) / 1s < runLimit) {
       if (index <= 92) {
            fibonacci<long long>(index, previous);
            index++;
            Index++;
        }
        else {
            fibonacci<BigNumber>(Index, Previous);
            Index++;
        }
        
    }
    if (index <= 92) {
        cout << index << endl;
    }
    else {
        cout << Index << endl;
    }
    return 0;
}