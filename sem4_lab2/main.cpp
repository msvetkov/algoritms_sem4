#include "Huffman.h"
#include <iostream>

using namespace std;

int main() {
	cout << "Enter string > ";
	string sourceString;
	cin >> sourceString;
	Huffman* huffman = new Huffman(sourceString);
	cout << huffman->getDecodedStringMemoryInBits() << endl;
	cout << huffman->getIncodedStringMemoryInBits() << endl;
	cout << "Source string: " << huffman->getDecodedString() << endl;
	cout << "Result string: " << huffman->getIncodedString() << endl;
	cout << "Compression ratio: " << huffman->getCompressionRatioInPerc() << "%\n";
	cout << "Table of symbols and frequencies:\n";
	huffman->printTable();
	return 1;
}