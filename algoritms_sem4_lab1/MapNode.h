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
	MapNode(K key, V value) {
		this->key = key;
		this->value = value;
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
		this->color = Colors::RED;
	}

	MapNode() {
		this->parent = nullptr;
		this->left = nullptr;
		this->right = nullptr;
		this->color = Colors::BLACK;
	}

	K getKey() {
		return this->key;
	}

	V getValue() {
		return this->value;
	}

	void setColor(Colors color) {
		this->color = color;
	}

	Colors getColor() {
		return this->color;
	}

	void setParent(MapNode<K, V>* parent) {
		this->parent = parent;
	}

	MapNode<K, V>* getParent() {
		return this->parent;
	}

	void setLeft(MapNode<K, V>* left) {
		this->left = left;
	}

	MapNode<K, V>* getLeft() {
		return this->left;
	}

	void setRight(MapNode<K, V>* right) {
		this->right = right;
	}

	MapNode<K, V>* getRight() {
		return this->right;
	}
};


#endif // !MAP_NODE_H
