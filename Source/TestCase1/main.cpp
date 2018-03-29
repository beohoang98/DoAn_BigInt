#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define TEST_INPUT "../../test/test_input.txt"
#define TEST_OUTPUT "../../test/test_output.txt"
#define TEST_RESULT "../../test/test_result.txt"

int main() {

	_wchdir(L"../Debug/");
	string testProgramName = "1612001_1612009_1612023_1612085_1612154.exe";
	string command = testProgramName + " \"" + TEST_INPUT + "\" \"" + TEST_RESULT + "\"";

	cout << command << endl;
	system(command.c_str());

	ifstream fresult(TEST_RESULT);
	ifstream foutput(TEST_OUTPUT);

	if (!fresult.is_open()) {
		cout << "cannot open " << TEST_RESULT << endl;
		system("pause");
		return 0;
	}
	if (!foutput.is_open()) {
		cout << "cannot open " << TEST_OUTPUT << endl;
		system("pause");
		return 0;
	}

	int id = 0,
		cout_true = 0, 
		cout_false = 0;
	string expect_string, calc_string;
	while (!foutput.eof()) {
		foutput >> expect_string;
		fresult >> calc_string;

		bool isTrue = expect_string == calc_string;
		if (isTrue) ++cout_true; 
		else ++cout_false;

		cout << "Line " << id << (isTrue ? " TRUE " : " FALSE ") << endl;

		if (!isTrue) {
			cout << "\texpect:" << expect_string << endl
				<< "\t  calc:" << calc_string << endl;
		}

		++id;
	}

	fresult.close();
	foutput.close();

	cout << endl
		<< "TRUE: " << cout_true << "/" << id << "\t"
		<< "FALSE: " << cout_false << "/" << id <<endl;

	system("pause");
	return 0;
}