#define _CRT_SECURE_NO_WARNINGS

#include "BigInt.h"
#include <algorithm>

using namespace std;

BigInt::BigInt() {
	this->head = 0;
	memset(body, 0, 15 * sizeof(unsigned char));
}

//ultility function
string BigInt::chiaChuoiCho2(string dec, int &sodu) {
	string kq;

	sodu = 0;
	int pos = 0;
	if (dec[pos] == '-') {
		kq = '-';
		pos++;
	}

	while (pos < dec.length()) {
		int sochia = ((dec[pos] - '0') / 2 + sodu * 5) + '0';
		if (sochia > '0') kq.push_back(((dec[pos] - '0') / 2 + sodu * 5) + '0');
		
		sodu = (dec[pos] - '0') % 2;
		pos++;
	}

	return kq;
}


string BigInt::valueToBin(unsigned char value) {
	//chuyen 1 so 1byte thanh chuoi nhi phan

	if (value = 0) return "0";

	string result;
	while (value > 0) {
		char bit = value % 2;
		value /= 2;	
		result.push_back(bit + '0');
	}

	while (result[result.length() - 1] == '0') {
		result.pop_back();
	}
	reverse(result.begin(), result.end());
	return result;
}


string BigInt::valueToHex(unsigned char value) {
	//chuyen 1 so int thanh chuoi hexa
	char s[9];

	sprintf(s, "%X", value);

	return string(s);
}

BigInt::BigInt(string chuoiSo) {
	this->head = 0;
	memset(body, 0, 15 * sizeof(unsigned char));

	//check negative
	if (chuoiSo[0] == '-') {
		//gan bit 1 vao bit cao nhat
		head = head | (1 << 8);

		//bo dau - o dau chuoi ra
		chuoiSo.erase(0,1); 
	}
	

	//chuyen dec sang bit
	int sodu = 0;
	int pos = 0;
	while (chuoiSo != "") {
		chuoiSo = chiaChuoiCho2(chuoiSo, sodu);

		int vitri_trong_bit = pos % 8;
		int vitri_trong_mang = pos / 8;

		// su dung phep | de gan 1bit vao vi tri thu pos
		body[vitri_trong_mang] |= sodu << vitri_trong_bit;

		pos++;
	}
}

BigInt::BigInt(string chuoiSo, int coSo) {
	this->head = 0;
	memset(body, 0, 15 * sizeof(unsigned char));

	switch (coSo)
	{
	case 2:
	{///case block
		for (int len = chuoiSo.length(), pos = len - 1; pos >= 0; --pos) {
			int bit_hientai = chuoiSo[pos] - '0';

			int vitri_trong_bit = (len-pos-1) % 8;
			int vitri_trong_mang = (len-pos-1) / 8;

			// su dung phep | de gan 1bit vao vi tri thu pos
			body[vitri_trong_mang] |= bit_hientai << vitri_trong_bit;
		}
	}
	break;


	//case 8:
	//{//case block
	//	for (int len = chuoiSo.length(), pos = len - 1; pos >= 0; --pos) {
	//		int bit_hientai = chuoiSo[pos] - '0';

	//		int vitri_3bit_trong_byte = ((len - pos - 1) % 8) % 3;
	//		int vitri_trong_mang = (len - pos - 1) / 8;

	//		// su dung phep | de gan 1bit vao vi tri thu pos
	//		body[vitri_trong_mang] |= bit_hientai << 0;
	//	}
	//}
	//break;

	case 10:
		BigInt::BigInt(chuoiSo);
		break;

	case 16:
	{//case block
		//check negative
		if (chuoiSo[0] == '-') {
			//gan bit 1 vao bit cao nhat
			head = head | (1 << 8);
			//bo dau - o dau chuoi ra
			chuoiSo.erase(0, 1);
		}

		for (int len = chuoiSo.length(), pos = len - 1; pos >= 0; --pos) {
			int _4bit_hientai = HEX_VALUE.find(chuoiSo[pos]);

			int vitri_4bit_trong_byte = (len - pos - 1) % 2;
			int vitri_4bit_trong_mang = (len - pos - 1) / 2;

			// su dung phep | de gan 1bit vao vi tri thu pos
			body[vitri_4bit_trong_mang] |= _4bit_hientai << (vitri_4bit_trong_byte*4);
		}
	}
	break;

	default:
		throw new exception("Co so khong hop le");
		break;
	}
}

string BigInt::toString(int coSo) {
	string kq;
	bool isNegative = false;
	int start_block;


	//kiem tra bit cao nhat
	if (head & (1 << 8)) {
		//la so am
		kq = "1";

		start_block = 14;
		isNegative = true;
	}
	else {
		start_block = 14;
		while (body[start_block] == 0 && start_block >= 0) {
			--start_block;
		}
		if (start_block < 0) return "0";
	}

	switch (coSo) {
	case 2:
	{ // binary
		while (start_block >= 0) {
			string _8bit_string;
			unsigned char block_value = body[start_block];

			for (int i = 0; i < 8; ++i) {
				char bit = (block_value % 2);
				block_value /= 2;

				if (isNegative) bit = 1 - bit;
				_8bit_string.push_back(bit + '0');
			}

			reverse(_8bit_string.begin(), _8bit_string.end());
			kq += _8bit_string;
			--start_block;
		}
		while (kq.front() == '0') kq.erase(0, 1);
		//if (isNegative) { // bu 2
		//	int len = kq.length();
		//	kq[len - 1] = 1 - kq[len - 1];
		//}
	}
	break;


	case 8:
	{ // octave

	}
	break;


	case 10:
	{ // decimal

	}
	break;


	case 16:
	{ // heximal

	}
	break;

	default: //loi
		throw exception("co so khong ton tai");
		break;

	}

	return kq;
}

BigInt BigInt::operator+(const BigInt &A) {
	return BigInt();//de tam
}

BigInt BigInt::operator-(const BigInt &A) {
	return BigInt();//de tam
}

BigInt BigInt::operator*(const BigInt &A) {
	return BigInt();//de tam
}

BigInt BigInt::operator/(const BigInt &A) {
	return BigInt();//de tam
}

BigInt BigInt::operator&(const BigInt &A) {
	return BigInt();//de tam
}

BigInt BigInt::operator|(const BigInt &A) {
	return BigInt();//de tam
}

BigInt BigInt::operator^(const BigInt &A) {
	return BigInt();//de tam
}


BigInt operator~(const BigInt &A) {
	return BigInt();//de tam
}



BigInt BigInt::operator<<(int soBit) {
	return BigInt();//de tam
} //dich trai

BigInt BigInt::operator>>(int soBit) {
	return BigInt();//de tam
} //dich phai


BigInt::~BigInt()
{
}