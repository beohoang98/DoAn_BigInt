#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iostream>



using namespace std;

const string HEX_VALUE = "0123456789ABCDEF";

class BigInt
{
private:
	unsigned char body[16];

public:
	BigInt();//mac dinh la 0, co so 10
	BigInt(string chuoiSo);
	BigInt(string chuoiSo, int coSo); //neu khong de co so, co so mac dinh la 10

	string toString();
	string toString(int coSo); // chuyen thanh chuoi voi he co so, mac dinh la 10

	//phep toan
	BigInt operator+(const BigInt &)const;
	BigInt operator-(const BigInt &)const;
	BigInt operator*(const BigInt &)const;
	BigInt operator/(const BigInt &)const;
	BigInt operator%(const BigInt &)const;
	BigInt operator&(const BigInt &)const; //AND
	BigInt operator|(const BigInt &)const; //OR
	BigInt operator^(const BigInt &)const; //XOR
	
	BigInt _divide(const BigInt&, BigInt&)const;
	BigInt negative() const;
	//so sanh
	int compare(const BigInt &)const;
	bool operator>(const BigInt &)const;
	bool operator<(const BigInt &)const;
	bool operator==(const BigInt &)const;
	bool operator>=(const BigInt &)const;
	bool operator<=(const BigInt &)const;

	friend BigInt operator~(const BigInt &); // phep NOT, chi tac dung len chinh minh

	BigInt operator<<(int soBit)const; //dich trai
	BigInt operator>>(int soBit)const; //dich phai
	

	///ultility function
	static string chiaChuoiCho2(string, int&);
	static string nhanChuoiCho2(string, int);
	

	~BigInt();
};

//ham yeu cau
bool* DecToBin(BigInt x);
BigInt BinToDec(bool *bit);
char *BinToHex(bool *bit);
char *DecToHex(BigInt x);