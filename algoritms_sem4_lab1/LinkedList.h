#pragma once

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include "ListNode.h"

template<class T>
class LinkedList {
private:
	ListNode<T>* head;
	ListNode<T>* tail;

public:
	LinkedList();

	void insert(T value);

	void removeLast();

	bool equals(LinkedList* list);

	void print();

	void clear();

	~LinkedList();
};


#endif
