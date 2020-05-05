#ifndef LIST_NODE_H
#define LIST_NODE_H

template<class T>
class ListNode {
private:
	T data;
	ListNode<T>* next;
public:
	ListNode(T data) {
		this->setData(data);
		this->next = nullptr;
	}

	T getData() {
		return this->data;
	}

	void setData(T data) {
		this->data = data;
	}

	ListNode<T>* getNext() {
		return this->next;
	}

	void setNext(ListNode<T>* next) {
		this->next = next;
	}
};


#endif
