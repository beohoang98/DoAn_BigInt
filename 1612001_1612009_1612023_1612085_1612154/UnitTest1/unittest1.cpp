#include "stdafx.h"
#include "../1612001_1612009_1612023_1612085_1612154/BigInt.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(Test1)
	{
	public:
		///Test Khoi tao
		TEST_METHOD(TestKhoiTao_DEC) {
			BigInt A("10050", 10);
			Assert::AreEqual("10050", A.toString().c_str());
		}
		TEST_METHOD(TestKhoiTao_HEX) {
			BigInt A("FFAADD", 16);
			Assert::AreEqual("FFAADD", A.toString(16).c_str());
		}
		TEST_METHOD(TestKhoiTao_BIN) {
			BigInt A("00001001100", 2);
			Assert::AreEqual("1001100", A.toString(2).c_str());
		}
		TEST_METHOD(TestKhoiTao_DEC_NEGATIVE) {
			BigInt A("-10050", 10);
			Assert::AreEqual("-10050", A.toString().c_str());
		}

		///Test Chuyen doi co so
		TEST_METHOD(Test_HEX_TO_BIN) {
			BigInt A("F0FF", 16);
			Assert::AreEqual("1111000011111111", A.toString(2).c_str());
		}
		TEST_METHOD(Test_BIN_TO_HEX) {
			BigInt A("10101111", 2);
			Assert::AreEqual("AF", A.toString(16).c_str());
		}
		TEST_METHOD(Test_DEC_TO_BIN) {
			BigInt A("15", 10);
			Assert::AreEqual("1111", A.toString(2).c_str());
		}
		TEST_METHOD(Test_DEC_TO_HEX_MINUS) {
			BigInt A("-1", 10);
			/// 128 bits is 1
			Assert::AreEqual("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", A.toString(16).c_str());
		}
		TEST_METHOD(Test_DEC_TO_HEX_MINUS_2) {
			BigInt A("-1655", 10);
			/// 128 bits is 1
			Assert::AreEqual("FFFFFFFFFFFFFFFFFFFFFFFFFFFFF989", A.toString(16).c_str());
		}
		TEST_METHOD(Test_DEC_TO_HEX_MINUS_3) {
			BigInt A("-16546545", 10);
			/// 128 bits is 1
			Assert::AreEqual("FFFFFFFFFFFFFFFFFFFFFFFFFF03850F", A.toString(16).c_str());
		}
		

		///Test phep toan
		TEST_METHOD(TestCongSoNho)
		{
			BigInt A("101010", 2);
			BigInt B("100011", 2);
			BigInt C = A + B;
			Assert::AreEqual("1001101", C.toString(2).c_str());
		}

		TEST_METHOD(TestCongSoLon_20)
		{
			BigInt A("15320102001048988945");
			BigInt B("1891281982");
			BigInt C = A + B;
			Assert::AreEqual("15320102002940270927", C.toString(10).c_str());
		}

		TEST_METHOD(TestCongSoLon_35)
		{
			BigInt A("123456789012345678901234567890111111");
			BigInt B("123451234512345123451234512345");
			BigInt C = A + B;
			Assert::AreEqual("123456912463580191246358019124623456", C.toString(10).c_str());
		}

		TEST_METHOD(TruSoNho)
		{
			BigInt A("1501");
			BigInt B("333");
			BigInt C = A - B;
			Assert::AreEqual("1168", C.toString().c_str());
		}

		TEST_METHOD(TruSoLon_20)
		{
			BigInt A("4568795465");
			BigInt B("98765432198765432100");
			BigInt C = A - B;
			Assert::AreEqual("-98765432194196636635", C.toString().c_str());
		}

		TEST_METHOD(TruSoLon_35)
		{
			BigInt A("123456789012345678901234567890111111");
			BigInt B("123451234512345123451234512345");
			BigInt C = A - B;
			Assert::AreEqual("123456665561111166556111116655598766", C.toString(10).c_str());
		}

		TEST_METHOD(TestNhanSoNho)
		{
			BigInt A("3");
			BigInt B("12");
			BigInt C = A * B;
			Assert::AreEqual("36", C.toString(10).c_str());
		}

		TEST_METHOD(TestNhanSoLon)
		{
			BigInt A("123123123123123123");
			BigInt B("456456456");
			BigInt C = A * B;
			Assert::AreEqual("56200344432432432376232088", C.toString(10).c_str());
		}

		TEST_METHOD(TestNhan_Duong_Am) {
			BigInt A("123123123123123123");
			BigInt B("-456456456");
			BigInt C = A * B;
			Assert::AreEqual("-56200344432432432376232088", C.toString(10).c_str());
		}

		TEST_METHOD(TestNhan_Am_Am) {
			BigInt A("-123123123123123123");
			BigInt B("-456456456");
			BigInt C = A * B;
			Assert::AreEqual("56200344432432432376232088", C.toString(10).c_str());
		}


		//test and or xor not
		TEST_METHOD(TEST_AND) {
			BigInt A("12564231321564");
			BigInt B("895613215645");
			BigInt C = A & B;
			Assert::AreEqual("274987033500", C.toString().c_str());
		}
		TEST_METHOD(TEST_OR) {
			BigInt A("4549856123156");
			BigInt B("8798561231564652132156");
			BigInt C = A | B;
			Assert::AreEqual("8798561231712023478076", C.toString().c_str());
		}
		TEST_METHOD(TEST_XOR) {
			BigInt A("4549856123156");
			BigInt B("8798561231564652132156");
			BigInt C = A ^ B;
			Assert::AreEqual("8798561227309538700840", C.toString().c_str());
		}
		TEST_METHOD(TEST_NOT) {
			BigInt A("8798561227309538700840");
			BigInt B = ~A;
			BigInt C = A + B;
			Assert::AreEqual("-1", C.toString().c_str());
		}
	};
}