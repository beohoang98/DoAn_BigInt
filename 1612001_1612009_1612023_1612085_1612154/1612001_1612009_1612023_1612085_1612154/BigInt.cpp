#include "BigInt.h"

using namespace std;

BigInt::BigInt() {

}

BigInt::BigInt(string chuoiSo) {

}

BigInt::BigInt(string chuoiSo, int coSo) {

}

string BigInt::toString(int coSo) {

	return "Day la so nguyen lon";
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




istream& operator>>(istream& is_gi_do, BigInt& A) {

	return is_gi_do; // nua m sua lai
}
ostream& operator<<(ostream& os_gi_do, const BigInt& A) {

	return os_gi_do; // nua m sua lai
}



BigInt::~BigInt()
{
}
