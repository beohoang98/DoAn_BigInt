#include <iostream>
#include "../1612001_1612009_1612023_1612085_1612154/BigInt.h"


int main() {
	BigInt A("255");
	BigInt C = A << 12;
	
	cout << C.toString() << endl;
	system("pause");
	return 0;
}