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
	
	if (dec == "0") return "0";

	string kq;

	sodu = 0;
	int pos = 0;
	if (dec[pos] == '-') {
		kq = '-';
		pos++;
	}

	while (pos < dec.length()) {
		int sochia = (dec[pos] - '0') / 2 + sodu * 5;
		kq.push_back(sochia + '0');
		
		sodu = (dec[pos] - '0') % 2;
		pos++;
	}
	while (kq.front() == '0' && kq.length() > 1) kq.erase(0, 1);

	return kq;
}
string BigInt::nhanChuoiCho2(string dec, int add_value) {
	string kq = "";

	int overflow_prev = add_value;
	int pos = dec.length()-1;

	while (pos >= 0) {
		int donvi_nhan = (dec[pos] - '0') * 2 + overflow_prev;
		overflow_prev = donvi_nhan / 10;
		donvi_nhan = donvi_nhan % 10;

		kq.push_back(donvi_nhan + '0');
		pos--;
	}
	if (overflow_prev) {
		kq.push_back('1');
	}
	reverse(kq.begin(), kq.end());

	return kq;
}



BigInt::BigInt(string chuoiSo) : BigInt(chuoiSo, 10) {
	// neu khong noi gi, mac dinh chuoi truyen vo la he co so 10
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

	case 10:
	{
		//kiem tra so am
		if (chuoiSo[0] == '-') {
			head = head | (1 << 7);
			chuoiSo.erase(0, 1);
		}

		//chuyen dec sang bit
		int sodu = 0;
		int pos = 0;
		while (chuoiSo != "0") {
			chuoiSo = chiaChuoiCho2(chuoiSo, sodu);
			//tim vi tri cua bit
			int vitri_trong_bit = pos % 8;
			int vitri_trong_mang = pos / 8;
			// su dung phep | de gan 1bit vao vi tri thu pos
			body[vitri_trong_mang] |= sodu << vitri_trong_bit;
			pos++;
		}
	}
	break;

	case 16:
	{//case block
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




//chuyen thanh chuoi
string BigInt::toString() {
	//mac dinh la xuat ra chuoi he so thap phan
	return this->toString(10);
}

string BigInt::toString(int coSo) {
	string kq;
	bool isNegative = false;
	int start_block;


	//kiem tra bit cao nhat
	if (head & (1 << 7)) {
		//la so am
		start_block = 15;
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
			unsigned char block_value = (start_block < 15) ? body[start_block] : (head & 127);

			for (int i = 0; i < 8; ++i) {
				char bit = (block_value % 2);
				block_value /= 2;

				//if (isNegative) bit = 1 - bit;
				_8bit_string.push_back(bit + '0');
			}

			reverse(_8bit_string.begin(), _8bit_string.end());
			kq += _8bit_string;
			--start_block;
		}
		while (kq.front() == '0') kq.erase(0, 1);
	}
	break;


	case 10:
	{ // decimal
		kq = "0";
		int pos = (start_block+1) * 8;

		while (pos >= 0) {
			int vitri_trong_bit = pos % 8;
			int vitri_block = pos / 8;
			char bit = body[vitri_block] & (1 << vitri_trong_bit);
			int add_bit = bit ? 1 : 0;

			kq = nhanChuoiCho2(kq, add_bit);
			--pos;
		}
	}
	break;


	case 16:
	{ // heximal
		while (start_block >= 0) {
			string _4bit_string;
			unsigned char block_value = (start_block < 15) ? body[start_block] : (head & 127);

			while (block_value > 0) {
				char hex = block_value % 16;
				block_value /= 16;
				_4bit_string.push_back(HEX_VALUE[hex]);
			}

			reverse(_4bit_string.begin(), _4bit_string.end());
			kq += _4bit_string;
			--start_block;
		}
		while (kq.front() == '0') kq.erase(0, 1);
	}
	break;

	default: //loi
		throw exception("co so khong ton tai");
		break;

	}

	return kq;
}





/// CAC XU LY TOAN TU 2 NGOI
BigInt BigInt::operator+(const BigInt &A) {
	BigInt res;
	if (head < 0 && A.head<0)		//cả 2 đều âm
	{

	}
	if (head < 0)
	{

	}
	if (A.head < 0)
	{

	}
	//cả 2 đều dương
	char du = 0;
	for (int i = 0; i < 15; i++)
	{
		int tmp = body[i] + A.body[i] + du;
		res.body[i] = tmp % 256;
		du = tmp / 256;
	}
	res.head = (head + A.head + du) & 127;

	return res;
}

BigInt BigInt::operator-(const BigInt &A) {
	BigInt res;
	if (*this == A)
		return res;
	if (head < 0 && A.head<0)		//cả 2 đều âm
	{

	}
	if (head < 0)
	{

	}
	if (A.head < 0)
	{

	}

	//cả 2 đều dương
	if (*this<A)		
	{

	}
	
	char nho = 0;
	for (int i = 0; i < 15; i++)
	{
		int tmp = body[i] - A.body[i] - nho;
		if (tmp < 0)
		{
			nho = 1;
			tmp += 256;
		}
		else
			nho = 0;
		res.body[i] = tmp;
	}
	res.head = (head - A.head - nho) & 127;
	return res;
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

int BigInt::compare(const BigInt &A)
{
	//Chưa xử lý số âm

	//so sánh 2 số có ít nhất 1 số dương
	if (head > A.head)
		return 1;
	if (head<A.head) 
		return -1;
	for (int i = 14; i >= 0; i--)
	{
		if (body[i]>A.body[i])
			return 1;
		if (body[i]<A.body[i])
			return -1;
	}
	return 0;
}

bool BigInt::operator>(const BigInt &A) {
	return compare(A) == 1;
}

bool BigInt::operator<(const BigInt &A) {
	return compare(A) == -1;
}

bool BigInt::operator==(const BigInt &A) {
	return compare(A) == 0;
}

bool BigInt::operator>=(const BigInt &A) {
	return compare(A)>-1;
}

bool BigInt::operator<=(const BigInt &A) {
	return compare(A) < 1;
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