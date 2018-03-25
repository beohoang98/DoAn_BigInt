#include <iostream>
#include "../1612001_1612009_1612023_1612085_1612154/BigInt.h"


int main() {

	BigInt A("8798561227309538700840");
	BigInt B = ~A;
	BigInt C = A + B;

	cout << (100 + ~(100)) << endl;
	
	system("pause");
	return 0;
}