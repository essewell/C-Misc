// Factorial of n = 1*2*3*...*n

#include <iostream>
using namespace std;

int factorial(int n) {
    if (n > 1) {
        cout << n;
        return n * factorial(n - 1);
    }
    else {
        return 1;
    }
}

int main() {
    int n, result;

    cout << "Enter a number: ";
    cin >> n;

    result = factorial(n);
    cout << "Factorial of " << n << " = " << result;
    return 0;
}
