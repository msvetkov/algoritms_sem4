#pragma once

#ifndef TREE_MAP_H
#define TREE_MAP_H

#include <string>
#include "LinkedList.h"
#include "MapNode.h"

template<class K, class V>
class TreeMap {
private:
	MapNode<K, V>* root;
	MapNode<K, V>* emptyLeaf;

	void rotateLeft(MapNode<K, V>* node);

	void rotateRight(MapNode<K, V>* node);

	void insertWithRotate(MapNode<K, V>* node);

	void removeWithRotate(MapNode<K, V>* node);

	void transplant(MapNode<K, V>* firstNode, MapNode<K, V>* secondNode);

	MapNode<K, V>* getNodeWithMinValue(MapNode<K, V>* node);

	void addKeys(LinkedList<K>* list, MapNode<K, V>* node);

	void addValues(LinkedList<V>* list, MapNode<K, V>* node);

	MapNode<K, V>* findNodeByKey(K key);

	void printRecoursive(MapNode<K, V>* elem);
public:
	TreeMap();

	void insert(K key, V value);

	void remove(K key);

	V find(K key);

	LinkedList<K>* getKeys();	

	LinkedList<V>* getValues();

	void print();

	void clear();

	~TreeMap();
};


#endif
