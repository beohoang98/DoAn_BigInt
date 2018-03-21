#pragma once

#include <string>
#include <regex>

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
private:
	regex checkTinhToan;
	regex checkQuyDoi;
public:
	string source;
	int loai;

	XuLyInput(string input) {
		source = input;
		loai = -1;

		checkTinhToan = regex("^(\\d+) (\\w+) (.+) (\\w+)$");
		checkQuyDoi = regex("^(\\d+) (\\d+) (\\w+)$");
	};

	int check(int * &soTraVe, string * &chuoiTraVe) { // kiem tra input co hop le hay khong va tra ve cac tham so
		
		if (chuoiTraVe != NULL) free(chuoiTraVe);
		if (soTraVe != NULL) free(soTraVe);
		smatch match;
		
		if (regex_match(source, match, checkTinhToan)) {
			string chuoiCoSo = match[1].str();
			string phepToan = match[3].str();
			int coSo = atoi(chuoiCoSo.c_str());

			if (coSo != 2 && coSo != 8 && coSo != 10 && coSo != 16)
				return KHONG_HOP_LE;

			soTraVe = new int[2]; //Co so & phep toan
			soTraVe[0] = coSo;

			if (phepToan == "+") soTraVe[1] = PHEP_CONG;
			else if (phepToan == "-") soTraVe[1] = PHEP_TRU;
			else if (phepToan == "*") soTraVe[1] = PHEP_NHAN;
			else if (phepToan == "/") soTraVe[1] = PHEP_CHIA;
			else if (phepToan == "&") soTraVe[1] = PHEP_AND;
			else if (phepToan == "|") soTraVe[1] = PHEP_OR;
			else if (phepToan == "^") soTraVe[1] = PHEP_XOR;
			else if (phepToan == "~") soTraVe[1] = PHEP_NOT;
			else if (phepToan == "<<") soTraVe[1] = PHEP_DICH_TRAI;
			else if (phepToan == ">>") soTraVe[1] = PHEP_DICH_PHAI;
			else return KHONG_HOP_LE;

			chuoiTraVe = new string[2];
			chuoiTraVe[0] = match[2].str();
			chuoiTraVe[1] = match[4].str();

			return TINH_TOAN;
		}


		else if (regex_match(source, match, checkQuyDoi)) {

			string coSo1 = match[1].str();
			string coSo2 = match[2].str();

			soTraVe = new int[2]; //2 co so
			soTraVe[0] = atoi(coSo1.c_str());
			soTraVe[1] = atoi(coSo2.c_str());

			chuoiTraVe = new string[1]; //so duy nhat can doi
			chuoiTraVe[0] = match[3].str();

			return QUY_DOI;
		}


		return KHONG_HOP_LE;
	}	

	~XuLyInput() {
		cout << "Hello world!" << endl;
	}
};

