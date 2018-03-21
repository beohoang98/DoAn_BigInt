#include "../1612001_1612009_1612023_1612085_1612154/BigInt.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	int sodu = 10;
	BigInt A ("13B", 16);
	BigInt B("13C",16);
	BigInt C = A + B;

	cout << A.toString(10) << endl << A.toString(10) << endl << C.toString(10) << endl;

	system("pause");

	return 0;
}