#include "./Huffman.h"

Huffman::Huffman(std::string sourceString) {
	this->calculate(sourceString);
}

void Huffman::buildTable(Node* root, LinkedList<bool>& code, TreeMap<char, bool*>& table) {
	if (root->getLeft()) {
		code.insert(0);
		this->buildTable(root->getLeft(), code, table);
	}

	if (root->getRight()) {
		code.insert(1);
		this->buildTable(root->getRight(), code, table);
	}

	if (root->getSymbol()) {
		bool* bitArray = new bool[code.length()];
		for (size_t i = 0; i < code.length(); i++) {
			bitArray[i] = code.at(i);
		}
		table.remove(root->getSymbol());
		table.insert(root->getSymbol(), bitArray);
	}

	if (code.length()) {
		code.removeLast();
	}
}

bool Huffman::compareNodes(Node* first, Node* second) {
	return first->getFrequency() >= second->getFrequency();
}

void Huffman::buildTree(LinkedList<Node*>& tree) {
	while (tree.length() != 1) {
		tree.sort(&compareNodes);

		Node* left = tree.at(0);
		tree.removeFront();
		Node* right = tree.at(0);
		tree.removeFront();
		Node* parent = new Node(left, right);
		tree.insert(parent);
	}
}

void Huffman::calculate(std::string str) {
	this->decodedString = str;
	TreeMap<char, int>* map = new TreeMap<char, int>();
	TreeMap<char, bool*> table;
	int decodeMemory = 0;
	int incodeMemory = 0;
	size_t strLength = str.length();

	for (size_t i = 0; i < strLength; i++) {
		int f = 0;
		if (map->containsKey(str[i])) {
			f = map->find(str[i]);
			map->remove(str[i]);
		} else {
			table.insert(str[i], nullptr);
		}
		map->insert(str[i], f + 1);
		decodeMemory += sizeof(str[i]);
	}
	this->decodeStringMemory = decodeMemory * 8;

	LinkedList<MapNode<char, int>*>* keyValuePairs = map->getNodesList();
	LinkedList<Node*> tree;
	for (size_t i = 0; i < keyValuePairs->length(); i++) {
		MapNode<char, int>* keyValuePair = keyValuePairs->at(i);
		tree.insert(
			new Node(keyValuePair->getKey(), keyValuePair->getValue())
		);
	}

	this->buildTree(tree);

	Node* root = tree.at(0);
	LinkedList<bool> listCode;
	this->buildTable(root, listCode, table);
	int arraySize;
	std::string incodedString = "";
	for (size_t i = 0; i < strLength; i++) {
		arraySize = sizeof(table.find(str[i])) / sizeof(table.find(str[i])[0]);
		incodeMemory += arraySize;
		for (int j = 0; j < arraySize; j++) {
			char symbol = table.find(str[i])[j] ? '1' : '0';
			incodedString += symbol;
		}
	}

	this->incodedString = incodedString;
	this->incodeStringMemory = incodeMemory * 8;

	this->compressionRatio = (float) incodeMemory / decodeMemory;
	this->table = map;
}

int Huffman::getDecodedStringMemoryInBits() {
	return this->decodeStringMemory;
}

int Huffman::getIncodedStringMemoryInBits() {
	return this->incodeStringMemory;
}

int Huffman::getCompressionRatioInPerc() {
	return (int) this->compressionRatio * 100;
}

std::string Huffman::getDecodedString() {
	return this->decodedString;
}

std::string Huffman::getIncodedString() {
	return this->incodedString;
}

void Huffman::printTable() {
	this->table->print();
}
