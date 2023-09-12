
#include <iostream>
#include <cmath>
using namespace std

int getBitPatternLength(const int array_size){
	int bit_pattern_length;
	cout << "Enter the required bit pattern length between 1 and " << array_size << ": ";
	cin >> bit_pattern_length;
	while (bit_pattern_length < 1 || bit_pattern_length > array_size)
	{
		cout << "You must enter between 1 and " << array_size << ". Enter again please: ";
		cin >> bit_pattern_length;
	}
	return bit_pattern_length;
}
void printArray(const int arr[], const int bit_pattern_length)
{
	for (int i = 0; i < bit_pattern_length; i++)
		cout << arr[i];
}
int selectComputation()
{
	cout << "Select your computation" << endl;
	cout << " 1. Unsigned Binary Representation Computation" << endl;
	cout << " 2. Sign and Magnitude Representation Computation" << endl;
	cout << " 3. Two's Complement Representation Computation" << endl;
	cout << " 4. Exit Program" << endl;
	int selection;
	cout << "Enter your selection (1, 2, 3, or 4): ";
	cin >> selection;
	while (selection != 1 && selection != 2 && selection != 3 && selection != 4)
	{
		cout << "Please enter a correct choice: ";
		cin >> selection;
	}
	return selection;
}

int main()
{
	cout << "This program demonstrates numeric information representation using" << endl;
	cout << " *** Unsigned Binary Representation" << endl;
	cout << " *** Sign and Magnitude Binary Representation" << endl;
	cout << " *** Two's Complement Binary Representation" << endl << endl;
	cout << "In addition, the program demonstrates" << endl;
	cout << " *** Two's complement binary addition, and" << endl;
	cout << " *** Conversion from two's complement to decimal." << endl << endl;
	const int array_size = 32;
	do
	{
		int selection = selectComputation();
		if (selection == 1)
		{
			int A[array_size];
			int bit_pattern_length = getBitPatternLength(array_size);
			int num;
			cout << "Enter a non-negative integer: ";
			cin >> num;
			while (num < 0){
				cout << "You must enter a non-negative integer. Enter again please: ";
				cin >> num;
			}
			computeUnsignedBinary(A, bit_pattern_length, num);
			cout << "The unsigned binary representation of " << num << " in " <<
				bit_pattern_length << " bit is ";
			printArray(A, bit_pattern_length);
			cout << endl;
		}
		else if (selection == 2)
		{
			int A[array_size];
			int bit_pattern_length = getBitPatternLength(array_size);
			int num;
			cout << "Enter an integer: ";
			cin >> num;
			computeSignAndMagnitudeBinary(A, bit_pattern_length, num);
			cout << "The sign and magnitude binary representation of " << num << " in " <<
				bit_pattern_length << " bit is ";
			printArray(A, bit_pattern_length);
			cout << endl;
		}
		else if (selection == 3)
		{
			int A1[array_size], A2[array_size], A3[array_size];
			int bit_pattern_length = getBitPatternLength(array_size);
			int num1, num2;
			cout << "Enter an integer: ";
			cin >> num1;
			computeTwosComplementBinary(A1, bit_pattern_length, num1);
			cout << "The two's complement binary representation of " << num1 << " in " <<
				bit_pattern_length << " bit is ";
			printArray(A1, bit_pattern_length);
			cout << endl;
			cout << "Enter a second integer: ";
			cin >> num2;
			computeTwosComplementBinary(A2, bit_pattern_length, num2);
			cout << "The two's complement binary representation of " << num2 << " in " <<
				bit_pattern_length << " bit is ";
			printArray(A2, bit_pattern_length);
			cout << endl;
			binaryAddition(A1, A2, bit_pattern_length, A3);
			cout << "The binary sum of ";
			printArray(A1, bit_pattern_length);
			cout << " and ";
			printArray(A2, bit_pattern_length);
			cout << " is ";
			printArray(A3, bit_pattern_length);
			cout << endl;
			int sum = twosComplementBinaryToDecimal(A3, bit_pattern_length);
			cout << "The integer value of the binary sum is " << sum << endl;
			if (sum == num1 + num2)
				cout << "This is a correct result." << endl;
			else
				cout << "This is not correct result because our bit pattern is too small to store the result." << endl;
		}
		else
			break;
		system("Pause");
		cout << endl << endl;
	} while (true);
	system("Pause");
	return 0;
}


