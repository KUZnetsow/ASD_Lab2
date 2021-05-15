#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab2_Kuznetsov/FanoAlgorithm.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		FanoAlgorithm* f1 = new FanoAlgorithm("it is test string");
		FanoAlgorithm* f2 = new FanoAlgorithm("Algorithms and data structures");
		FanoAlgorithm* f3 = new FanoAlgorithm("ab");
		TEST_METHOD(TestEncoding)
		{
			Assert::AreEqual((string)"1011110010101110011010011111000111100111010010000", f1->getEncodedStr());
			Assert::AreEqual((string)"0011000011010000111110001001110101101010101110101000010101111010011110011110010101011111110011000010111011011000001011", f2->getEncodedStr());
			Assert::AreEqual((string)"10", f3->getEncodedStr());
		}
		TEST_METHOD(TestDecoding) {
			Assert::AreEqual((string)"it is test string", f1->getDecodedStr());
			Assert::AreEqual((string)"Algorithms and data structures", f2->getDecodedStr());
			Assert::AreEqual((string)"ab", f3->getDecodedStr());
		}
		TEST_METHOD(TestSize) {
			Assert::AreEqual(136, (int)f1->initStrSizeInBites());
			Assert::AreEqual(240, (int)f2->initStrSizeInBites());
			Assert::AreEqual(16, (int)f3->initStrSizeInBites());
			Assert::AreEqual(49, (int)f1->encodedStrSizeInBites());
			Assert::AreEqual(118, (int)f2->encodedStrSizeInBites());
			Assert::AreEqual(2, (int)f3->encodedStrSizeInBites());
		}
	};
}
