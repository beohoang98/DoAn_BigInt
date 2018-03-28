#define _CRT_SECURE_NO_WARNINGS

#include "BigInt.h"
#include <algorithm>

using namespace std;

BigInt::BigInt() {
	memset(body, 0, 16 * sizeof(unsigned char));
}

//ultility function
string BigInt::chiaChuoiCho2(string dec, int &sodu) {
	if (dec == "0") return "0";
	string kq;
	bool isNegative = false;
	unsigned char pos = 0;
	sodu = 0;

	if (dec[0] == '-') {
		isNegative = true;
		pos++;
	}

	while (pos < dec.length()) {
		int sochia = (dec[pos] - '0') / 2 + sodu * 5;
		kq.push_back(sochia + '0');
		sodu = (dec[pos] - '0') % 2;
		pos++;
	}

	while (kq.front() == '0' && kq.length() > 1) kq.erase(0, 1);
	if (isNegative) kq.insert(0, "-");

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
	memset(body, 0, 16 * sizeof(unsigned char));

	switch (coSo)
	{
	case 2:
		{///case block
			for (int len = chuoiSo.length(), pos = len - 1; pos >= 0; --pos) {
				int bit_hientai = chuoiSo[pos] - '0';

				int vitri_trong_bit = (len-pos-1) % 8;
				int vitri_trong_mang = (len-pos-1) / 8;

				// su dung phep | de gan 1bit vao vi tri thu pos
				body[vitri_trong_mang] ^= bit_hientai << vitri_trong_bit;
			}
		}
		break;

	case 10:
		{
			bool isNegative = 0;
			//kiem tra so am
			if (chuoiSo[0] == '-') {
				memset(body, 0xFF, 16);
				isNegative = true;
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

				// su dung phep ^ de gan 1bit vao vi tri thu pos
				body[vitri_trong_mang] ^= (sodu << vitri_trong_bit);
				pos++;
			}
			if (isNegative) {
				pos = 0;
				sodu = 1;
				while (sodu && pos < 15) {
					if (body[pos] == 0xFF) {
						body[pos] = 0;
						sodu = 1;
					}
					else {
						body[pos] += sodu;
						sodu = 0;
					}
				}
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


	//kiem tra head
	if (body[15] & (1 << 7)) {
		isNegative = 1;
	}
	start_block = 15;
	while (body[start_block] == 0 && start_block >= 0) {
		--start_block;
	}
	if (start_block < 0) return "0";


	switch (coSo) {
	case 2:
	{ // binary
		while (start_block >= 0) {
			string _8bit_string;
			unsigned char block_value = body[start_block];

			for (int i = 0; i < 8; ++i) {
				char bit = (block_value % 2);
				block_value /= 2;
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
		unsigned char * block = new unsigned char[16];
		// day bit tam de chuyen ve thap phan
		memcpy(block, body, 16);
		
		if (isNegative) {
			int so_du = 1;
			int block_pos = 0;
			for (int i = 0; i < 16; ++i) {
				block[i] ^= 0xFF;
			}
			while (so_du != 0 && block_pos < 16) {
				if (block[block_pos] == 0xFF) {
					block[block_pos] = 0;
					so_du = 1;
				}
				else {
					block[block_pos] += so_du;
					so_du = 0;
				}
			}
		}

		kq = "0";
		int pos = (start_block+1)*8 - 1;// bo di bit cao nhat

		while (pos >= 0) {
			int vitri_trong_bit = pos % 8;
			int vitri_block = pos / 8;

			char bit = (block[vitri_block] & (1 << vitri_trong_bit));
			int add_bit = bit ? 1 : 0;

			kq = nhanChuoiCho2(kq, add_bit);
			--pos;
		}
		if (isNegative) kq.insert(0, "-");

		free(block);
	}
	break;


	case 16:
	{ // heximal
		while (start_block >= 0) {
			string _4bit_string;
			unsigned char block_value = body[start_block];

			for (int i = 0; i < 2; ++i) { // 1 bytes co 2 so hex
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
BigInt BigInt::operator+(const BigInt &A)const {
	BigInt result;
	char du = 0;
	for (int i = 0; i < 16; i++)
	{
		int tmp = body[i] + A.body[i] + du;
		result.body[i] = tmp % 256;
		du = tmp / 256;
	}

	return result;
}

BigInt BigInt::operator-(const BigInt &A)const {
	//BigInt res("0");
	//if (*this == A)
	//	return res; //tra ve 0
	//
	//char nho = 0;
	//for (int i = 0; i < 16; i++)
	//{
	//	int tmp = body[i] - A.body[i] - nho;
	//	if (tmp < 0)
	//	{
	//		nho = 1;
	//		tmp += 256;
	//	}
	//	else
	//		nho = 0;
	//	res.body[i] = tmp;
	//}
	////res.head = (head - A.head - nho) & 127;
	//return res;

	return (*this) + (A.negative());
}

BigInt BigInt::operator*(const BigInt &A)const {
	BigInt res;
	int tmp = 0, nho = 0;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j <= i; j++)
			tmp += body[j] * A.body[i - j];
		tmp += nho;
		res.body[i] = tmp % 256;
		nho = tmp / 256;
		tmp = 0;
	}

	return res;
}

BigInt BigInt::operator/(const BigInt &B)const {
	BigInt soDu;
	return this->_divide(B, soDu);
}

BigInt BigInt::operator%(const BigInt &B)const {
	BigInt soDu;
	this->_divide(B, soDu);
	return soDu;
}

BigInt BigInt::operator&(const BigInt &A) const {
	BigInt res;
	for (int i = 0; i < 16; i++)
		res.body[i] = body[i] & A.body[i];
	return res;
}

BigInt BigInt::operator|(const BigInt &A) const {
	BigInt res;
	for (int i = 0; i < 16; i++)
		res.body[i] = body[i] | A.body[i];
	//res.head = head|A.head;
	return res;
}

BigInt BigInt::operator^(const BigInt &A) const {
	BigInt res;
	for (int i = 0; i < 16; i++)
		res.body[i] = body[i] ^ A.body[i];
	//res.head = head^A.head;
	return res;
}

BigInt BigInt::_divide(const BigInt& B, BigInt& soDu)const {
	if ((*this) == BigInt("0"))
		return *this;
	if (B == BigInt("0")) {
		throw new exception("Loi chia cho 0");
		return BigInt("0");
	}

	BigInt Q = *this;
	BigInt A("0");
	BigInt M = B;

	char oneIsNegative = 0;//false

	if (Q.body[15] & 128) {
		Q = Q.negative();
		oneIsNegative = 1 - oneIsNegative;// toggle true/false
	}
	if (M.body[15] & 128) {
		M = M.negative();
		oneIsNegative = 1 - oneIsNegative;// toggle true/false
	}

	for (int i = 0; i < 128; ++i) {
		A = (A << 1);
		if (Q.body[15] & 128) {
			A.body[0] |= 1;
		}
		else {
			A.body[0] &= 254;
		}
		Q = Q << 1;

		A = A - M;
		if (A.body[15] & 128) {
			A = A + M;
			Q.body[0] = Q.body[0] & 254; // 1111 1110
		}
		else {
			Q.body[0] = Q.body[0] | 1; // 0000 0001
		}
	}

	if (oneIsNegative) {
		if (B.body[15] & 128)
			soDu = B + A;
		else
			soDu = B - A;
		return Q.negative();
	}
	else {
		soDu = A;
		return Q;
	}
}

BigInt BigInt::negative() const
{
	BigInt zero("0", 10);
	if ((*this) == zero)
		return zero;

	BigInt res = ~(*this);

	int so_du = 1;
	int pos = 0;
	while (so_du != 0 && pos < 16) {
		if (res.body[pos] == 0xFF) {
			res.body[pos] = 0;
			so_du = 1;
		}
		else {
			res.body[pos] += so_du;
			so_du = 0;
		}
	}
	
	return res;
}

int BigInt::compare(const BigInt &B)const
{
	int isA_negative = body[15] & (1<<7); // so voi bit thu 8
	int isB_negative = B.body[15] & (1 << 7);

	if (isA_negative && isB_negative) {
		// ca 2 deu am, doi chieu so sanh
		return B.compare(*this);
	}
	else if (isA_negative) {
		return -1;
	}
	else if (isB_negative) {
		return 1;
	}

	for (int i = 15; i >= 0; i--)
	{
		if (body[i]>B.body[i])
			return 1;
		if (body[i]<B.body[i])
			return -1;
	}

	return 0;
}

bool BigInt::operator>(const BigInt &A)const {
	return compare(A) == 1;
}

bool BigInt::operator<(const BigInt &A)const {
	return compare(A) == -1;
}

bool BigInt::operator==(const BigInt &A)const {
	return compare(A) == 0;
}

bool BigInt::operator>=(const BigInt &A)const {
	return compare(A)>-1;
}

bool BigInt::operator<=(const BigInt &A)const {
	return compare(A) < 1;
}


BigInt operator~(const BigInt &A) {
	BigInt result;
	for (int i = 0; i < 16; i++)
		result.body[i] = A.body[i] ^ 0xFF;
	return result;
}



BigInt BigInt::operator<<(int soBit) const {
	if (soBit <= 0) throw new exception("shift left error");

	BigInt result = (*this);

	char isNegative = result.body[15] & 128;
	if (isNegative) {
		result = ~result;
	}

	int soBitDich = soBit % 8;
	int soByteDich = soBit / 8;

	if (soByteDich > 0) {
		for (int i = 15; i >= soByteDich; --i) {
			result.body[i] = result.body[i - soByteDich];
		}
		memset(result.body, 0, soByteDich);
	}
	if (soBitDich == 0) return result;

	//when soBitDich > 0
	unsigned char nho_old = result.body[0] >> (8 - soBitDich),
				nho_new = 0;
	result.body[0] = (unsigned char)(result.body[0] << soBitDich);

	for (int i = 1; i < 16; ++i) {
		nho_new = result.body[i] >> (8 - soBitDich);
		unsigned char saukhiDich = (result.body[i] << soBitDich);
		result.body[i] = saukhiDich | nho_old;
		nho_old = nho_new;
		nho_new = 0;
	}

	if (isNegative) {
		result = ~result;
	}

	return result;
} //dich trai

BigInt BigInt::operator>>(int soBit) const {
	if (soBit <= 0) throw new exception("shift right error");

	BigInt result = (*this);

	char isNegative = result.body[15] & 128;
	if (isNegative) {
		result = ~result;
	}

	int soBitDich = soBit % 8;
	int soByteDich = soBit / 8;

	if (soByteDich > 0) {
		for (int i = 0; i < 16 - soByteDich; ++i) {
			result.body[i] = result.body[i + soByteDich];
		}

		//gan phan con lai = 0
		for (int i = 16 - soByteDich; i < 16; ++i) {
			result.body[i] = 0;
		}
	}
	if (soBitDich == 0) return result;

	//when soBitDich > 0
	unsigned char nho_old = result.body[15] << (8 - soBitDich),
		nho_new = 0;
	result.body[15] = (unsigned char)(result.body[15] >> soBitDich);

	for (int i = 14; i >= 0; --i) {
		nho_new = result.body[i] << (8 - soBitDich);
		unsigned char saukhiDich = (result.body[i] >> soBitDich);
		result.body[i] = saukhiDich | nho_old;
		nho_old = nho_new;
		nho_new = 0;
	}

	if (isNegative) {
		result = ~result;
	}
	return result;
} //dich phai


BigInt::~BigInt()
{
}



//ham yeu cau
bool * DecToBin(BigInt x) {
	string binStr = x.toString(2);
	int len = binStr.length();

	bool * bin = new bool[128];
	memset(bin, 0, sizeof(bool)* 128);
	
	for (int i = 0; i < len; ++i) {
		bin[len - i - 1];
	}

	return bin;
}

BigInt BinToDec(bool * bit) {
	string binStr;
	while (bit) {
		binStr.insert(0, (*bit ? "1" : "0"));
		bit++;
	}

	return BigInt(binStr);
}

char * BinToHex(bool *bit) {
	string hexStr = BinToDec(bit).toString(16);
	
	char * s = new char[hexStr.length() + 1];
	strcpy(s, hexStr.c_str());

	return s;
}

char *DecToHex(BigInt x) {
	string hexStr = x.toString(16);

	char * s = new char[hexStr.length() + 1];
	strcpy(s, hexStr.c_str());

	return s;
}