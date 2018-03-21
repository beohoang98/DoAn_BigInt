#include "../1612001_1612009_1612023_1612085_1612154/BigInt.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	BigInt A ("FFFFFF", 16);

	cout << A.toString(10) << endl;

	system("pause");

	return 0;
}