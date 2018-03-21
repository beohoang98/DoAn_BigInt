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


	string toString(int coSo); // chuyen thanh chuoi voi he co so, mac dinh la 10


	//phep toan
	BigInt operator+(const BigInt &);
	BigInt operator-(const BigInt &);
	BigInt operator*(const BigInt &);
	BigInt operator/(const BigInt &);
	BigInt operator&(const BigInt &); //AND
	BigInt operator|(const BigInt &); //OR
	BigInt operator^(const BigInt &); //XOR
	int compare(const BigInt &);
	bool operator>(const BigInt &);
	bool operator<(const BigInt &);
	bool operator==(const BigInt &);
	bool operator>=(const BigInt &);
	bool operator<=(const BigInt &);
	friend BigInt operator~(const BigInt &); // phep NOT, chi tac dung len chinh minh

	BigInt operator<<(int soBit); //dich trai
	BigInt operator>>(int soBit); //dich phai
	

	///ultility function
	static string chiaChuoiCho2(string, int&);
	static string nhanChuoiCho2(string, int);
	static string valueToBin(unsigned char value);
	static string valueToHex(unsigned char value);
	

	~BigInt();
};

//ham yeu cau
//bool* DecToBin(BigInt X);

