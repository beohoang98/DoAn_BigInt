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
			BigInt A("01001100", 2);
			Assert::AreEqual("01001100", A.toString(2).c_str());
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
		

		///Test phep toan
		TEST_METHOD(TestCongSoNho)
		{
			BigInt A("101010", 2);
			BigInt B("100011", 2);
			BigInt C = A + B;
			Assert::AreEqual("1001101", C.toString(2).c_str());
		}

		TEST_METHOD(TestCongSoLon)
		{
			BigInt A("15320102001048988945");
			BigInt B("1891281982");
			BigInt C = A + B;
			Assert::AreEqual("15320102002940270927", C.toString(10).c_str());
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
	};
}