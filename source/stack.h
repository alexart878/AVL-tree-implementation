#pragma once
#include <iostream>
#include "spisok.h"

template <typename T>
class stack : public list<T> {

public:
	stack();
	~stack();
	bool notempty();
	T top();
	void push(T val);
	void pop();

private:
	list<T>* newstack;
};

template <typename T>
stack<T>::stack() {
	newstack = new list<T>;
}

template <typename T>
stack<T>::~stack() {
	delete newstack;
}

template <typename T>
bool stack <T>::notempty() {
	return newstack->head;
}

template <typename T>
T stack<T>::top() {
	//if (newstack->head == nullptr) return NULL;
	return newstack->head->val;
}

template <typename T>
void stack<T>::push(T val) {
	newstack->addnode(val);
}

template <typename T>
void stack<T>::pop() {
	if (newstack->head) newstack->deletenode();
}
