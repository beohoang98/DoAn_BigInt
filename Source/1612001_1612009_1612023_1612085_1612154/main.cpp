#include <iostream>
#include <fstream>
#include "XuLyInput.h"
#include "BigInt.h"

using namespace std;

int main(int argc, char ** argv) {

	//xu ly tham so truyen vao
	string input_path;
	string output_path;
	if (argc < 2) {
		cout << "Chua co duong dan den input va output" << endl;
		//debug
		/*input_path = "../Debug/input.txt";
		output_path = "../Debug/output.txt";*/
		return 0;
	}
	else {
		input_path = argv[1];
		output_path = argv[2];
	}

	ifstream fin(input_path);
	ofstream fout(output_path);
	if (!fin.is_open()) {
		cout << "Khong tim thay file input hoac duong dan khong hop le" << endl;
		return 0;
	}
	if (!fout.is_open()) {
		cout << "Khong the tao file ouput hoac duong dan khong hop le" << endl;
		return 0;
	}


	//VONG LAP DOC DU LIEU VAO
	while (!fin.eof()) {
		string input_line;
		int *soTraVe = NULL;//luu cac gia tri so
		string *chuoiTraVe = NULL;//luu cac gia tri chuoi

		getline(fin, input_line); //1 bieu thuc tren 1 dong

		XuLyInput xuly(input_line);
		int loai = xuly.check(soTraVe, chuoiTraVe);

		try {
			if (loai == TINH_TOAN) {
				int coSo = soTraVe[0];
				int toanTu = soTraVe[1];

				if (toanTu == PHEP_DICH_TRAI || toanTu == PHEP_DICH_PHAI) {
					BigInt A(chuoiTraVe[0], coSo);
					int soBit = atoi(chuoiTraVe[1].c_str()); // so thu 2 la mot so nguyen (ko lon)

					BigInt KQ;

					if (toanTu == PHEP_DICH_TRAI) KQ = A << soBit;
					else KQ = A >> soBit;

					fout << KQ.toString(coSo);
				}
				else {
					BigInt * A = new BigInt(chuoiTraVe[0], coSo); //chuyen chuoi thanh so nguyen
					BigInt * B = new BigInt(chuoiTraVe[1], coSo); //	voi co so cho truoc
					BigInt KQ;

					switch (toanTu) {
					case PHEP_CONG:
						KQ = *A + *B;
						fout << KQ.toString(coSo) << endl;
						//fout << A.toString(coSo) << " cong " << A.toString(coSo) << endl;
						break;

					case PHEP_NHAN:
						KQ = *A * *B;
						fout << KQ.toString(coSo) << endl;
						//fout << A.toString(coSo) << " nhan " << A.toString(coSo) << endl;
						break;

					case PHEP_CHIA:
						KQ = *A / *B;
						fout << KQ.toString(coSo) << endl;
						//fout << A.toString(coSo) << " chia " << A.toString(coSo) << endl;
						break;

					case PHEP_TRU:
						KQ = *A - *B;
						fout << KQ.toString(coSo) << endl;
						//fout << A.toString(coSo) << " tru " << A.toString(coSo) << endl;
						break;

					case PHEP_AND:
						KQ = *A & *B;
						fout << KQ.toString(coSo) << endl;
						//fout << A.toString(coSo) << " & " << A.toString(coSo) << endl;
						break;

					case PHEP_OR:
						KQ = *A | *B;
						fout << KQ.toString(coSo) << endl;
						//fout << A.toString(coSo) << " | " << A.toString(coSo) << endl;
						break;

					case PHEP_XOR:
						KQ = *A ^ *B;
						fout << KQ.toString(coSo) << endl;
						//fout << A.toString(coSo) << " ^ " << A.toString(coSo) << endl;
						break;

					case PHEP_NOT: // Phep NOT chua ro rang...
						/*KQ = *A + ~(*B);
						fout << KQ.toString(coSo) << endl;*/
						break;

					default:
						fout << "phep toan khong hop le" << endl;
						break;
					}
				}

			}
			else if (loai == QUY_DOI) {
				int coSoDau = soTraVe[0];
				int coSoCuoi = soTraVe[1];

				BigInt * soCanDoi = new BigInt(chuoiTraVe[0], coSoDau);

				fout << soCanDoi->toString(coSoCuoi) << endl;
				free(soCanDoi);
			}
			else {
				fout << "input khong hop le" << endl;
			}
		}
		catch (exception * e) {
			fout << e->what() << endl;
			cout << e->what() << endl;
			free(e);
		}
	}

	fin.close();
	fout.close();
	return 0;
}