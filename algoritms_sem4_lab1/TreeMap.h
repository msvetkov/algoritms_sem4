#ifndef TREE_MAP_H
#define TREE_MAP_H

#include "LinkedList.h"
#include "MapNode.h"

template<class K, class V>
class TreeMap {
private:
	MapNode<K, V>* root;
	MapNode<K, V>* emptyLeaf;

	void rotateLeft(MapNode<K, V>* node) {
		MapNode<K, V>* currentNode = node->getRight();
		node->setRight(currentNode->getLeft());
		if (currentNode->getLeft() != this->emptyLeaf) {
			currentNode->getLeft()->setParent(node);
		}
		currentNode->setParent(node->getParent());
		if (node->getParent() == this->emptyLeaf) {
			this->root = currentNode;
		} else if (node == node->getParent()->getLeft()) {
			node->getParent()->setLeft(currentNode);
		} else {
			node->getParent()->setRight(currentNode);
		}
		currentNode->setLeft(node);
		node->setParent(currentNode);
	}

	void rotateRight(MapNode<K, V>* node) {
		MapNode<K, V>* currentNode = node->getLeft();
		node->setLeft(currentNode->getRight());
		if (currentNode->getRight() != this->emptyLeaf) {
			currentNode->getRight()->setParent(node);
		}
		currentNode->setParent(node->getParent());
		if (node->getParent() == this->emptyLeaf) {
			this->root = currentNode;
		} else if (node == node->getParent()->getRight()) {
			node->getParent()->setRight(currentNode);
		} else {
			node->getParent()->setLeft(currentNode);
		}
		currentNode->setRight(node);
		node->setParent(currentNode);
	}

	void insertWithRotate(MapNode<K, V>* node) {
		MapNode<K, V>* currentNode = nullptr;
		while (node->getParent()->getColor() == Colors::RED) {
			if (node->getParent() == node->getParent()->getParent()->getLeft()) {
				currentNode = node->getParent()->getParent()->getRight();
				if (currentNode->getColor() == Colors::RED) {
					node->getParent()->setColor(Colors::BLACK);
					currentNode->setColor(Colors::BLACK);
					node->getParent()->getParent()->setColor(Colors::RED);
					node = node->getParent()->getParent();
				} else {
					if (node == node->getParent()->getRight()) {
						node = node->getParent();
						this->rotateLeft(node);
					}
					node->getParent()->setColor(Colors::BLACK);
					node->getParent()->getParent()->setColor(Colors::RED);
					this->rotateRight(node->getParent()->getParent());
				}
			} else {
				currentNode = node->getParent()->getParent()->getLeft();
				if (currentNode->getColor() == Colors::RED) {
					node->getParent()->setColor(Colors::BLACK);
					currentNode->setColor(Colors::BLACK);
					node->getParent()->getParent()->setColor(Colors::RED);
					node = node->getParent()->getParent();
				} else {
					if (node == node->getParent()->getLeft()) {
						node = node->getParent();
						this->rotateRight(node);
					}
					node->getParent()->setColor(Colors::BLACK);
					node->getParent()->getParent()->setColor(Colors::RED);
					this->rotateLeft(node->getParent()->getParent());
				}
			}
		}
		root->setColor(Colors::BLACK);
	}

	void removeWithRotate(MapNode<K, V>* node) {
		MapNode<K, V>* deletingNode = nullptr;
		while (node != this->emptyLeaf && node->getColor() == Colors::BLACK) {
			if (node == node->getParent()->getLeft()) {
				deletingNode = node->getParent()->getRight();
				if (deletingNode->getColor() == Colors::RED) {
					deletingNode->setColor(Colors::BLACK);
					node->getParent()->setColor(Colors::RED);
					this->rotateLeft(node->getParent());
					deletingNode = node->getParent()->getRight();
				}
				if (deletingNode->getLeft()->getColor() == Colors::BLACK && deletingNode->getRight()->getColor() == Colors::BLACK) {
					deletingNode->setColor(Colors::RED);
					node = node->getParent();
				} else if (deletingNode->getRight()->getColor() == Colors::BLACK) {
					deletingNode->getLeft()->setColor(Colors::BLACK);
					deletingNode->setColor(Colors::RED);
					this->rotateRight(deletingNode);
					deletingNode = node->getParent()->getRight();
				}
				deletingNode->setColor(node->getParent()->getColor());
				node->getParent()->setColor(Colors::BLACK);
				deletingNode->getRight()->setColor(Colors::BLACK);
				this->rotateLeft(node->getParent());
				node = this->root;
			} else {
				deletingNode = node->getParent()->getLeft();
				if (deletingNode->getColor() == Colors::RED) {
					deletingNode->setColor(Colors::BLACK);
					node->getParent()->setColor(Colors::RED);
					this->rotateRight(node->getParent());
					deletingNode = node->getParent()->getLeft();
				} if (deletingNode->getRight()->getColor() == Colors::BLACK && deletingNode->getLeft()->getColor() == Colors::BLACK) {
					deletingNode->setColor(Colors::RED);
					node = node->getParent();
				} else if (deletingNode->getLeft()->getColor() == Colors::BLACK) {
					deletingNode->getRight()->setColor(Colors::BLACK);
					deletingNode->setColor(Colors::RED);
					this->rotateLeft(deletingNode);
					deletingNode = node->getParent()->getLeft();
				}
				deletingNode->setColor(node->getParent()->getColor());
				node->getParent()->setColor(Colors::BLACK);
				deletingNode->getLeft()->setColor(Colors::BLACK);
				this->rotateRight(node->getParent());
				node = this->root;
			}
		}
	}

	void transplant(MapNode<K, V>* firstNode, MapNode<K, V>* secondNode) {
		if (firstNode->getParent() == this->emptyLeaf) {
			this->root = secondNode;
		} else if (firstNode == firstNode->getParent()->getLeft()) {
			firstNode->getParent()->setLeft(secondNode);
		} else {
			firstNode->getParent()->setRight(secondNode);
		}
		secondNode->setParent(firstNode->getParent());
	}

	MapNode<K, V>* getNodeWithMinValue(MapNode<K, V>* node) {
		while (node->getLeft() != this->emptyLeaf) {
			node = node->getLeft();
		}
		return node;
	}

	void addKeys(LinkedList<K>* list, MapNode<K, V>* node) {
		if (node != this->emptyLeaf) {
			this->addKeys(list, node->getLeft());
			list->insert(node->getKey());
			this->addKeys(list, node->getRight());
		}
	}

	void addValues(LinkedList<V>* list, MapNode<K, V>* node) {
		if (node != this->emptyLeaf) {
			this->addValues(list, node->getLeft());
			list->insert(node->getValue());
			this->addValues(list, node->getRight());
		}
	}

	void addNodes(LinkedList<MapNode<K, V>*>* list, MapNode<K, V>* node) {
		if (node != this->emptyLeaf) {
			this->addNodes(list, node->getLeft());
			list->insert(node);
			this->addNodes(list, node->getRight());
		}
	}

	MapNode<K, V>* findNodeByKey(K key) {
		MapNode<K, V>* node = this->root;
		while (node != this->emptyLeaf) {
			if (node->getKey() == key) {
				break;
			}

			if (key < node->getKey()) {
				node = node->getLeft();
			} else {
				node = node->getRight();
			}
		}

		if (node != this->emptyLeaf) {
			return node;
		} else {
			throw std::invalid_argument("This key doesn't exist");
		}
	}

	void printRecoursive(MapNode<K, V>* node) {
		std::cout << "  " << node->getKey() << ": " << node->getValue() << ";\n";

		if (node->getLeft() != this->emptyLeaf) {
			this->printRecoursive(node->getLeft());
		}
		if (node->getRight() != this->emptyLeaf) {
			this->printRecoursive(node->getRight());
		}
	}
public:
	TreeMap() {
		this->emptyLeaf = new MapNode<K, V>();
		this->root = this->emptyLeaf;
		this->root->setParent(emptyLeaf);
	}

	void insert(K key, V value) {
		MapNode<K, V>* node = new MapNode<K, V>(key, value);
		MapNode<K, V>* y = this->emptyLeaf;
		MapNode<K, V>* x = this->root;

		while (x != this->emptyLeaf) {
			y = x;
			if (node->getKey() < x->getKey()) {
				x = x->getLeft();
			}
			else {
				x = x->getRight();
			}
		}

		node->setParent(y);
		if (y == this->emptyLeaf) {
			this->root = node;
		}
		else if (node->getKey() < y->getKey()) {
			y->setLeft(node);
		}
		else {
			y->setRight(node);
		}

		node->setLeft(this->emptyLeaf);
		node->setRight(this->emptyLeaf);
		this->insertWithRotate(node);
	}

	void remove(K key) {
		MapNode<K, V>* node = this->findNodeByKey(key);
		MapNode<K, V>* x = nullptr;
		if (node->getLeft() == this->emptyLeaf) {
			this->transplant(node, node->getRight());
		} else if (node->getRight() == this->emptyLeaf) {
			this->transplant(node, node->getLeft());
		} else {
			MapNode<K, V>* y = this->getNodeWithMinValue(node->getRight());
			Colors yColor = y->getColor();
			x = y->getRight();
			if (y->getParent() == node) {
				x->setParent(y);
			} else {
				this->transplant(y, y->getRight());
				y->setRight(node->getRight());
				y->getRight()->setParent(y);
			}
			this->transplant(node, y);
			y->setLeft(node->getLeft());
			y->getLeft()->setParent(y);
			y->setColor(node->getColor());
			if (yColor == Colors::BLACK) {
				this->removeWithRotate(x);
			}
		}
	}

	V find(K key) {
		MapNode<K, V>* node = this->findNodeByKey(key);
		return node->getValue();
	}

	LinkedList<K>* getKeys() {
		LinkedList<K>* list = new LinkedList<K>();
		this->addKeys(list, root);
		return list;
	}

	LinkedList<V>* getValues() {
		LinkedList<V>* list = new LinkedList<V>();
		this->addValues(list, root);
		return list;
	}

	void print() {
		std::cout << "{\n";
		this->printRecoursive(this->root);
		std::cout << "}\n";
	}

	void clear() {
		while (this->root != this->emptyLeaf) {
			this->remove(root->getKey());
		}
	}

	bool containsKey(K key) {
		bool result = true;
		try {
			this->find(key);
		}
		catch (std::invalid_argument error) {
			result = false;
		}
		return result;
	}

	LinkedList<MapNode<K, V>*>* getNodesList() {
		LinkedList<MapNode<K, V>*>* list = new LinkedList<MapNode<K, V>*>();
		this->addNodes(list, this->root);
		return list;
	}

	~TreeMap() {
		this->clear();
	}
};


#endif
