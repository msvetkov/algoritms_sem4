#pragma once

#ifndef LIST_NODE_H
#define LIST_NODE_H

template<class T>
class ListNode {
private:
	T data;
	ListNode<T>* next;
public:
	ListNode(T data);

	T getData();

	void setData(T data);

	ListNode<T>* getNext();

	void setNext(ListNode<T>* next);
};


#endif
