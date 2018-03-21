#include "stdafx.h"
#include "../1612001_1612009_1612023_1612085_1612154/BigInt.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(Test1)
	{
	public:

		TEST_METHOD(TestKhoiTao) {
			BigInt A("FFAADD", 16);

			Assert::AreEqual("FFAADD", A.toString(16).c_str());
		}
		
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
			Assert::AreEqual("56 200 344 432 432 432 376 232 088", C.toString(10).c_str());
		}
	};
}