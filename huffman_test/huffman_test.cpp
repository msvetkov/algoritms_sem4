#include "pch.h"
#include "CppUnitTest.h"

#include "../sem4_lab2/Huffman.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace huffmantest {
	Huffman* huffman;
	const std::string SOURCE_STRING = "programing";
	const std::string TARGET_STRING = "0000111100000111111100000011000100000111";

	TEST_CLASS(huffmantest) {
	public:
		TEST_METHOD_INITIALIZE(init) {
			huffman = new Huffman(SOURCE_STRING);
		}
		
		TEST_METHOD(getDecodedStringMemoryInBits) {
			Assert::AreEqual(huffman->getDecodedStringMemoryInBits(), 80);
		}

		TEST_METHOD(getIncodedStringMemoryInBits) {
			Assert::AreEqual(huffman->getIncodedStringMemoryInBits(), 320);
		}

		TEST_METHOD(getDecodedString) {
			Assert::AreEqual(huffman->getDecodedString(), SOURCE_STRING);
		}

		TEST_METHOD(getIncodedString) {
			Assert::AreEqual(huffman->getIncodedString(), TARGET_STRING);
		}

		TEST_METHOD(getCompressionRatioInPerc) {
			Assert::AreEqual(huffman->getCompressionRatioInPerc(), 400);
		}
	};
}
