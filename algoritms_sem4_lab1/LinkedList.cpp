#include "LinkedList.h"

template<class T>
LinkedList<T>::LinkedList() {
	this->head = nullptr;
	this->tail = nullptr;
}

template<class T>
void LinkedList<T>::insert(T value) {
	auto* newNode = new ListNode<T>(value);

	if (this->head) {
		this->tail->setNext(newNode);
		this->tail = newNode;
	} else {
		this->head = newNode;
		this->tail = this->head;
	}
}

template<class T>
void LinkedList<T>::print() {
	if (this->head) {
		ListNode<T>* current = this->head;
		std::cout << "[";
		while (current) {
			std::cout << current->getData();
			if (current->getNext()) {
				std::cout << ", ";
			}
			current = current->getNext();
		}
		std::cout << "]";
		std::cout << std::endl;
	}
}

template<class T>
bool LinkedList<T>::equals(LinkedList* list) {
	bool equal = true;
	if (!this->head && list->head || this->head && !list->head) {
		equal = false;
	}

	ListNode<T>* current = this->head;
	ListNode<T>* target = list->head;

	while (current && target) {
		if (current->getData() != target->getData()) {
			equal = false;
		}
		current = current->getNext();
		target = target->getNext();
	}
	return equal;
}

template<class T>
void LinkedList<T>::removeLast() {
	if (this->head) {
		ListNode<T>* current = this->head;
		if (!current->next) {
			delete current;
			this->head = nullptr;
			this->tail = nullptr;
		} else {
			while (current->next != this->tail) {
				current = current->getNext();
			}
			current->getNext() = nullptr;
			delete this->tail;
			this->tail = current;
		}
	}	
}

template<class T>
void LinkedList<T>::clear() {
	while (head) {
		this->removeLast();
	}
}

template<class T>
LinkedList<T>::~LinkedList() {
	this->clear();
}


