#pragma once

#include <string>
#include <iostream>

using namespace std;
class BigInt
{
private:

public:
	BigInt();//mac dinh la 0, co so 10
	BigInt(string chuoiSo);
	BigInt(string chuoiSo, int coSo); //neu khong de co so, co so mac dinh la 10

	string toString(int coSo); // chuyen thanh chuoi voi he co so, mac dinh la 10

	BigInt operator+(const BigInt &);
	BigInt operator-(const BigInt &);
	BigInt operator*(const BigInt &);
	BigInt operator/(const BigInt &);
	BigInt operator&(const BigInt &); //AND
	BigInt operator|(const BigInt &); //OR
	BigInt operator^(const BigInt &); //XOR

	friend BigInt operator~(const BigInt &); // phep NOT, chi tac dung len chinh minh

	BigInt operator<<(int soBit); //dich trai
	BigInt operator>>(int soBit); //dich phai
	
	friend istream& operator>>(istream&, BigInt&);
	friend ostream& operator<<(ostream&, const BigInt&);

	~BigInt();
};

