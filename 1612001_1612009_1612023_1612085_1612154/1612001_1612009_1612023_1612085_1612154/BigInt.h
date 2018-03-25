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
	char head;
	unsigned char body[15];
	

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
	BigInt operator&(const BigInt &); //AND
	BigInt operator|(const BigInt &); //OR
	BigInt operator^(const BigInt &); //XOR
	BigInt moveSign();
	//so sanh
	int compare(const BigInt &)const;
	bool operator>(const BigInt &)const;
	bool operator<(const BigInt &)const;
	bool operator==(const BigInt &)const;
	bool operator>=(const BigInt &)const;
	bool operator<=(const BigInt &)const;

	friend BigInt operator~(const BigInt &); // phep NOT, chi tac dung len chinh minh

	BigInt operator<<(int soBit); //dich trai
	BigInt operator>>(int soBit); //dich phai
	

	///ultility function
	static string chiaChuoiCho2(string, int&);
	static string nhanChuoiCho2(string, int);
	

	~BigInt();
};

//ham yeu cau
//bool* DecToBin(BigInt X);

