#include "Huffman.h"

int main() {
	std::string sourceString = "ExampleText";
	Huffman* huffman = new Huffman(sourceString);
	std::cout << "Source string: " << huffman->getDecodedString() << std::endl;
	std::cout << "Result string: " << huffman->getIncodedString() << std::endl;
	std::cout << "Compression ratio: " << huffman->getCompressionRatioInPerc() << "%\n";
	std::cout << "Table of symbols and frequencies:\n";
	huffman->printTable();
	return 1;
}