#include "stdafx.h"
#include "CppUnitTest.h"
#include "../OperatingSystemsProject/Block.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OSProjectUnitTest
{
	//check custom conversion function
	//TEST_CLASS(UnitTest1)
	//{
	//public:
	//	TEST_METHOD(TestMethod1)
	//	{
	//		Block block(0, 0);

	//		Drivers::Word word;
	//		word.letter1 = 65;
	//		word.letter2 = 66;

	//		__int16 number = block.convert_word_to_int16(word);
	//		int number2 = number;

	//		block.~Block();
	//		Assert::AreEqual(number2, 16706);
	//	}
	//};

	////check custom conversion function
	//TEST_CLASS(UnitTest2)
	//{
	//public:
	//	TEST_METHOD(TestMethod2)
	//	{
	//		Block block(0, 0);
	//		Drivers::Word word;
	//		__int16 number = 16706; // AB  01000001 01000010
	//		word = block.convert_int16_to_word(number);
	//		unsigned char number2 = 65;
	//		unsigned char number3 = 66;
	//		block.~Block();
	//		Assert::AreEqual(number2, word.letter1);
	//		Assert::AreEqual(number3, word.letter2);
	//	}
	//};
	//
	////check for conversion built into c++
	//TEST_CLASS(UnitTest3)
	//{
	//public:
	//	TEST_METHOD(TestMethod2)
	//	{
	//		unsigned int num1 = 16706;
	//		__int16 num2 = 16706;
	//		unsigned int num3 = num2;
	//		Assert::AreEqual(num3, num1);
	//	}
	//};
}