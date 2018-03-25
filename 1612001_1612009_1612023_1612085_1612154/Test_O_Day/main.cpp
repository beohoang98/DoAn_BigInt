#include <iostream>
#include "../1612001_1612009_1612023_1612085_1612154/BigInt.h"


int main() {

	//BigInt a("1", 10);
	//BigInt b("1238521851254587451210458745121455", 10);
	BigInt a("1329227995784914729205674490288144383", 10);
	BigInt b("-1329227995784914729205674490288144383", 10);
	
	/*BigInt c = a-b;
	cout << a.toString() << " - " << b.toString() << " = " << c.toString() << endl;*/
	BigInt c = a.moveSign();
	cout << " "<<a.toString() << endl;
	cout << c.toString() << endl;
	cout << b.toString() << endl;
	system("pause");
	return 0;
}