#include "TreeMap.h"

template<class K, class V>
TreeMap<K, V>::TreeMap() {
	this->emptyLeaf = new MapNode<K, V>();
	this->root = this->emptyLeaf;
	this->root->setParent(emptyLeaf);
}

template<class K, class V>
void TreeMap<K, V>::insert(K key, V value) {
	MapNode<K, V>* node = new MapNode<K, V>(key, value);
	MapNode<K, V>* y = this->emptyLeaf;
	MapNode<K, V>* x = this->root;

	while (x != this->emptyLeaf) {
		y = x;
		if (node->getKey() < x->getKey()) {
			x = x->getLeft();
		} else {
			x = x->getRight();
		}
	}

	node->setParent(y);
	if (y == this->emptyLeaf) {
		this->root = node;
	} else if (node->getKey() < y->getKey()) {
		y->setLeft(node);
	} else {
		y->setRight(node);
	}

	node->setLeft(this->emptyLeaf);
	node->setRight(this->emptyLeaf);
	this->insertWithRotate(node);
}

template<class K, class V>
void TreeMap<K, V>::insertWithRotate(MapNode<K, V>* node) {
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

template<class K, class V>
void TreeMap<K, V>::remove(K key) {
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

template<class K, class V>
void TreeMap<K, V>::removeWithRotate(MapNode<K, V>* node) {
	MapNode<K, V>* deletingNode = nullptr;
	while (node != this->emptyLeaf && node->getColor() == Colors::BLACK) {
		if (node == node->getParent()->getLeft()) {
			deletingNode = node->getParent()->getRight();
			if (deletingNode->getColor() == Colors::RED) {
				deletingNode->setColor(Colors::BLACK);
				node->getParent()->setColor(Colors::RED);
				this->rotateLeft(node->getParent());
				deletingNode = node->getParent()->getRight();
			} if (deletingNode->getLeft()->getColor() == Colors::BLACK && deletingNode->getRight()->getColor() == Colors::BLACK) {
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

template<class K, class V>
V TreeMap<K, V>::find(K key) {
	MapNode<K, V>* node = this->findNodeByKey(key);
	return node->getValue();
}

template<class K, class V>
LinkedList<K>* TreeMap<K, V>::getKeys() {
	LinkedList<K>* list = new LinkedList<K>();
	this->addKeys(list, root);
	return list;
}

template<class K, class V>
void TreeMap<K, V>::addKeys(LinkedList<K>* list, MapNode<K, V>* node) {
	if (node != this->emptyLeaf) {
		this->addKeys(list, node->getLeft());
		list->insert(node->getKey());
		this->addKeys(list, node->getRight());
	}
}

template<class K, class V>
LinkedList<V>* TreeMap<K, V>::getValues() {
	LinkedList<V>* list = new LinkedList<V>();
	this->addValues(list, root);
	return list;
}

template<class K, class V>
void TreeMap<K, V>::addValues(LinkedList<V>* list, MapNode<K, V>* node) {
	if (node != this->emptyLeaf) {
		this->addValues(list, node->getLeft());
		list->insert(node->getValue());
		this->addValues(list, node->getRight());
	}
}

template<class K, class V>
void TreeMap<K, V>::print() {
	std::cout << "{\n";
	this->printRecoursive(this->root);
	std::cout << "}\n";
}

template<class K, class V>
void TreeMap<K, V>::printRecoursive(MapNode<K, V>* node) {
	std::cout << "  " << node->getKey() << ": " << node->getValue() << ";\n";

	if (node->getLeft() != this->emptyLeaf) {
		this->printRecoursive(node->getLeft());
	}
	if (node->getRight() != this->emptyLeaf) {
		this->printRecoursive(node->getRight());
	}
}

template<class K, class V>
void TreeMap<K, V>::clear() {
	while (this->root != this->emptyLeaf) {
		this->remove(root->getKey());
	}
}

template<class K, class V>
void TreeMap<K, V>::rotateLeft(MapNode<K, V>* node) {
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

template<class K, class V>
void TreeMap<K, V>::rotateRight(MapNode<K, V>* node) {
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

template<class K, class V>
void TreeMap<K, V>::transplant(MapNode<K, V>* firstNode, MapNode<K, V>* secondNode) {
	if (firstNode->getParent() == this->emptyLeaf) {
		this->root = secondNode;
	} else if (firstNode == firstNode->getParent()->getLeft()) {
		firstNode->getParent()->setLeft(secondNode);
	} else {
		firstNode->getParent()->setRight(secondNode);
	}
	secondNode->setParent(firstNode->getParent());
}

template<class K, class V>
MapNode<K, V>* TreeMap<K, V>::getNodeWithMinValue(MapNode<K, V>* node) {
	while (node->getLeft() != this->emptyLeaf) {
		node = node->getLeft();
	}
	return node;
}

template<class K, class V>
MapNode<K, V>* TreeMap<K, V>::findNodeByKey(K key) {
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

template<class K, class V>
TreeMap<K, V>::~TreeMap() {
	this->clear();
}