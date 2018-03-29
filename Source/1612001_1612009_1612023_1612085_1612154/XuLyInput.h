#pragma once

#include <string>
#include <sstream>

using namespace std;

#define PHEP_CONG	0
#define PHEP_TRU	1
#define PHEP_NHAN	2
#define PHEP_CHIA	3

#define PHEP_AND	4
#define PHEP_OR		5
#define PHEP_XOR	6
#define PHEP_NOT	7

#define PHEP_DICH_TRAI	8
#define PHEP_DICH_PHAI	9

#define KHONG_HOP_LE	0
#define QUY_DOI			1
#define TINH_TOAN		2

class XuLyInput
{
public:
	string source;
	int loai;

	XuLyInput(string input) {
		source = input;
	};

	int check(int * &soTraVe, string * &chuoiTraVe) { // kiem tra input co hop le hay khong va tra ve cac tham so
		
		if (chuoiTraVe != NULL) free(chuoiTraVe);
		if (soTraVe != NULL) free(soTraVe);
		stringstream ssinput_check1; // for Tinh toan
		stringstream ssinput_check2; // for Quy doi
		ssinput_check1 << (source);
		ssinput_check2 << (source);

		int coSo1, coSo2;
		string toantu;
		string so1, so2;
		
		if (ssinput_check1 >> coSo1 >> so1 >> toantu >> so2) {
			soTraVe = new int[2]; //Co so & phep toan
			soTraVe[0] = coSo1;

			if (toantu == "+") soTraVe[1] = PHEP_CONG;
			else if (toantu == "-") soTraVe[1] = PHEP_TRU;
			else if (toantu == "*") soTraVe[1] = PHEP_NHAN;
			else if (toantu == "/") soTraVe[1] = PHEP_CHIA;
			else if (toantu == "&") soTraVe[1] = PHEP_AND;
			else if (toantu == "|") soTraVe[1] = PHEP_OR;
			else if (toantu == "^") soTraVe[1] = PHEP_XOR;
			else if (toantu == "~") soTraVe[1] = PHEP_NOT;
			else if (toantu == "<<") soTraVe[1] = PHEP_DICH_TRAI;
			else if (toantu == ">>") soTraVe[1] = PHEP_DICH_PHAI;
			else return KHONG_HOP_LE;

			chuoiTraVe = new string[2];
			chuoiTraVe[0] = so1;
			chuoiTraVe[1] = so2;

			return TINH_TOAN;
		}
		else if (ssinput_check2 >> coSo1 >> coSo2 >> so1) {

			soTraVe = new int[2]; //2 co so
			soTraVe[0] = coSo1;
			soTraVe[1] = coSo2;

			chuoiTraVe = new string[1]; //so duy nhat can doi
			chuoiTraVe[0] = so1;

			return QUY_DOI;
		}

		return KHONG_HOP_LE;
	}	

	~XuLyInput() {
		//cout << "Hello world!" << endl;
	}
};

