#pragma once
#ifndef MAP_NODE_H
#define MAP_NODE_H

enum Colors { BLACK, RED };

template<class K, class V>
class MapNode {
private:
	K key;
	V value;
	Colors color;
	MapNode<K, V>* parent;
	MapNode<K, V>* left;
	MapNode<K, V>* right;
public:
	MapNode(K key, V value);

	MapNode();

	K getKey();

	V getValue();

	void setColor(Colors color);

	Colors getColor();

	void setParent(MapNode<K, V>* parent);

	MapNode<K, V>* getParent();

	void setLeft(MapNode<K, V>* left);

	MapNode<K, V>* getLeft();

	void setRight(MapNode<K, V>* right);

	MapNode<K, V>* getRight();
};


#endif // !MAP_NODE_H
