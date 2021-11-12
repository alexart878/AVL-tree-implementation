#pragma once
#include <iostream>

template <typename T>
class list {

private:
	struct node;

public:
	class Iterator;
	node* head;
	node* tail;

public:
	list();
	~list();
	Iterator begin() const;
	Iterator end() const;
	void addnode(const T& val);
	void addlastnode(const T& val);
	void deletenode();
	void deletelastnode();
	size_t listsize();
	void listprint();

private:
	struct node {
		node() : next(nullptr) {}
		node(const T& t) : val(t), next(nullptr) {}
		T val;
		node* next;
	};
};

template <typename T>
list<T>::list() : head(nullptr) {}

template <typename T>
list<T>::~list() {
	while (head) deletenode();
}

template <typename T>
class list<T>::Iterator {

public:
	Iterator(node* Node) : node(Node) {}

	bool operator == (const Iterator& other) const {
		if (this == &other) {
			return true;
		}
		return node == other.node;
	}

	bool operator != (const Iterator& other) const {
		return !operator == (other);
	}

	T operator*() const {
		if (node) {
			return node->val;
		}
		return T();
	}

	void operator++() {
		if (node) {
			node = node->next;
		}
	}

private:
	node* node;
};

template <typename T>
typename list<T>::Iterator list<T>::begin() const {
	return Iterator(head);
}

template <typename T>
typename list<T>::Iterator list<T>::end() const {
	return Iterator(nullptr);
}

template <typename T>
void list<T>::addnode(const T& val) {
	node* container = new node(val);
	container->next = head;
	head = tail = container;
}

template <typename T>
void list<T>::addlastnode(const T& val) {
	if (head) {
		node* temp = new node;
		temp->val = val;
		temp->next = nullptr;

		if (!head) head = tail = new node; 
		else {
			tail->next = temp;
			tail = temp;
		}
	}
}

template <typename T>
void list<T>::deletenode() {
	if (head) {
		node* newhead = head->next;
		delete head;
		head = newhead;
	}
}

template <typename T>
void list<T>::deletelastnode() {
	if (head) {
		node* temp = new node;
		node* prev = new node;
		temp = head;
		while (temp->next != nullptr) {
			prev = temp;
			temp = temp->next;
		}
		tail = prev;
		prev->next = nullptr;
		delete temp;
	}
}

template <typename T>
size_t list<T>::listsize() {
	size_t size = 0;
	for (Iterator it = begin(); it != end(); ++it) ++size;
	return size;
}

template <typename T>
void list<T>::listprint() {
	for (Iterator count = begin(); count != end(); ++count) std::cout << *count << " ";
}
