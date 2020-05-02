#include "MapNode.h"

template<class K, class V>
MapNode<K, V>::MapNode(K key, V value) {
	this->key = key;
	this->value = value;
	this->parent = nullptr;
	this->left = nullptr;
	this->right = nullptr;
	this->color = Colors::RED;
}

template<class K, class V>
MapNode<K, V>::MapNode() {
	this->parent = nullptr;
	this->left = nullptr;
	this->right = nullptr;
	this->color = Colors::BLACK;
}

template<class K, class V>
K MapNode<K, V>::getKey() {
	return this->key;
}

template<class K, class V>
V MapNode<K, V>::getValue() {
	return this->value;
}

template<class K, class V>
void MapNode<K, V>::setColor(Colors color) {
	this->color = color;
}

template<class K, class V>
Colors MapNode<K, V>::getColor() {
	return this->color;
}

template<class K, class V>
void MapNode<K, V>::setParent(MapNode<K, V>* parent) {
	this->parent = parent;
}

template<class K, class V>
MapNode<K, V>* MapNode<K, V>::getParent() {
	return this->parent;
}

template<class K, class V>
void MapNode<K, V>::setLeft(MapNode<K, V>* left) {
	this->left = left;
}

template<class K, class V>
MapNode<K, V>* MapNode<K, V>::getLeft() {
	return this->left;
}

template<class K, class V>
void MapNode<K, V>::setRight(MapNode<K, V>* right) {
	this->right = right;
}

template<class K, class V>
MapNode<K, V>* MapNode<K, V>::getRight() {
	return this->right;
}
