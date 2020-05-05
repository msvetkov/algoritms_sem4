#pragma once

#ifndef NODE_H
#define NODE_H

class Node {
private:
	char symbol;
	int frequency;
	Node* left;
	Node* right;
public:
	Node(char symbol, int frequency);

	Node(Node* left, Node* right);

	char getSymbol();

	void setSymbol(char symbol);

	int getFrequency();

	void setFrequency(int frequency);

	Node* getLeft();

	void setLeft(Node* left);

	Node* getRight();

	void setRight(Node* right);
};


#endif
