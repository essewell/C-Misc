/******************************************************************************
;@
;@ Student Name 1: Emmett Sewell
;@ Student 1 #: 301565227
;@ Student 1 userid (email): esa97 (esa97@sfu.ca)
;@
;@ Student Name 2: Josh Hale
;@ Student 2 #: 301459827
;@ Student 2 userid (email): jvh (jvh@sfu.ca)
;@
;@ Helpers: none
;@
;@ Resources: https://github.com/Limeoats/BigNumber, used for BigNumber
;@
;@ Name: assign1.cpp
******************************************************************************/

#include <iostream>
#include <chrono>
#include <bignumber.h>

using namespace std;
using namespace std::chrono;

int main() {
	cout << "Do not change this line.  Enter a sequence of increasing Fibonacci indicies and -1 to stop input." << endl;
	long long input{0};
	BigNumber n1{0}, n2{1}, n3{0};
	while (input >= 0) {
		n1 = 0, n2 = 1 , n3 = 0;
		cin >> input;
		if (input == -1) {
			break;
		}
		for (BigNumber i = 0; i < input; i++) {
			n3 = (n1 + n2);
			n1 = n2;
			n2 = n3;
		}
		cout << n1 << "\n";
	}
	const int runLimit{2};
	n1 = 0, n2 = 1, n3 = 0;
	BigNumber a{0};
	time_point<steady_clock> start = steady_clock::now();
	while ((steady_clock::now() - start) / 1s < runLimit) {
		n3 = (n1 + n2);
		n1 = n2;
		n2 = n3;
		a++;
	}
	cout << n1 << "\n";
	cout << a;
	return 0;
}