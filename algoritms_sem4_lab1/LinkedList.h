#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include "ListNode.h"

template<class T>
class LinkedList {
private:
	ListNode<T>* head;
	ListNode<T>* tail;
	size_t size;
public:
	LinkedList() {
		this->head = nullptr;
		this->tail = nullptr;
		this->size = 0;
	}

	T at(size_t id) {
		if (id > this->size) {
			throw std::invalid_argument("Index is outside of list");
		}

		ListNode<T>* node = this->head;
		for (size_t i = 0; i < id; i++) {
			node = node->getNext();
		}

		return node->getData();
	}

	void insert(T value) {
		auto* newNode = new ListNode<T>(value);

		if (this->head) {
			this->tail->setNext(newNode);
			this->tail = newNode;
		}
		else {
			this->head = newNode;
			this->tail = this->head;
		}

		this->size++;
	}

	void insertRange(LinkedList<T>* list) {
		ListNode<T>* node = list->head;
		while (node != nullptr) {
			this->insert(node);
			node = node->getNext();
		}
		this->size += list->size();
	}

	void removeLast() {
		if (this->head) {
			ListNode<T>* current = this->head;
			if (!current->getNext()) {
				delete current;
				this->head = nullptr;
				this->tail = nullptr;
			}
			else {
				while (current->getNext() != this->tail) {
					current = current->getNext();
				}
				current->setNext(nullptr);
				delete this->tail;
				this->tail = current;
			}
			this->size--;
		} else {
			throw std::out_of_range("The list is empty");
		}
	}

	void removeFront() {
		if (this->head != this->tail) {
			ListNode<T>* temp = this->head;
			this->head = head->getNext();
			delete temp;
			this->size--;
		} else if (this->size != 0) {
			ListNode<T>* temp = this->head;
			this->head = this->tail = nullptr;
			delete temp;
			this->size = 0;
		} else {
			throw std::out_of_range("The list is empty");
		}
	}

	bool equals(LinkedList* list) {
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

	void print() {
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

	void clear() {
		while (head) {
			this->removeLast();
		}
		this->size = 0;
	}

	size_t length() {
		return this->size;
	}

	void sort(bool (*compare)(T, T)) {
		ListNode<T>* first = this->head;
		ListNode<T>* second = this->head->getNext();
		T temp;

		while (first->getNext()) {
			while (second) {
				if (compare(first->getData(), second->getData())) {
					temp = first->getData();
					first->setData(second->getData());
					second->setData(temp);
				}
				second = second->getNext();
			}
			first = first->getNext();
			second = first->getNext();
		}
	}

	~LinkedList() {
		this->clear();
	}
};


#endif
