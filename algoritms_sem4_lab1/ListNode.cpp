#include "ListNode.h"

template<class T>
ListNode<T>::ListNode(T data) {
	this->setData(data);
	this->next = nullptr;
}

template<class T>
T ListNode<T>::getData() {
	return this->data;
}

template<class T>
void ListNode<T>::setData(T data) {
	this->data = data;
}

template<class T>
ListNode<T>* ListNode<T>::getNext() {
	return this->next;
}

template<class T>
void ListNode<T>::setNext(ListNode<T>* next) {
	this->next = next;
}
