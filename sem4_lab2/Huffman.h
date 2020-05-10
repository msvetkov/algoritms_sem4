#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "Node.h"
#include "../algoritms_sem4_lab1/TreeMap.h"

class Huffman {
private:
	std::string decodedString;
	std::string incodedString;

	int decodeStringMemory;
	int incodeStringMemory;
	float compressionRatio;
	TreeMap<char, int>* table;

	void buildTable(Node* root, LinkedList<bool>& code, TreeMap<char, bool*> &table);
	void buildTree(LinkedList<Node*>& tree);
	static bool compareNodes(Node* first, Node* second);
	void calculate(std::string str);
public:
	Huffman(std::string sourceString);

	int getDecodedStringMemoryInBits();

	int getIncodedStringMemoryInBits();

	std::string getDecodedString();

	std::string getIncodedString();

	int getCompressionRatioInPerc();

	void printTable();

	~Huffman() = default;
};


#endif
