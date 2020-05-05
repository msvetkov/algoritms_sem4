#include "./Node.h"

Node::Node(char symbol, int frequency) {
    this->symbol = symbol;
    this->frequency = frequency;
}

Node::Node(Node* left, Node* right) {
    this->right = right;
    this->left = left;
}

char Node::getSymbol() {
	return this->symbol;
}

void Node::setSymbol(char symbol) {
	this->symbol = symbol;
}

int Node::getFrequency() {
	return this->frequency;
}

void Node::setFrequency(int frequency) {
	this->frequency = frequency;
}

Node* Node::getLeft() {
	return this->left;
}

void Node::setLeft(Node* left) {
	this->left = left;
}

Node* Node::getRight() {
	return this->right;
}

void Node::setRight(Node* right) {
	this->right = right;
}