#include <iostream>
#include "stack.h"

struct node {
	node(int val) {
		value = val;
		height = -1;
		left = right = nullptr;
	};

	node* left;
	node* right;
	int value;
	int height;
};

class avl {
public:

	node* root;
	avl() { root = nullptr; }

	void inorder(node* t);      //recursive
	void preorder(node* t);
	void postorder(node* t);

	void itinorder(node* t);    //iteratve
	void itpreorder(node* t);
	void itpostorder(node* t);  
	void levelorder(node* t);

	int height(node* t) {
		if (!t) return 0;
		return t->height;
	}

	void correctheight(node* t) {
		int heightleft = height(t->left);
		int heightright = height(t->right);

		t->height = std::max(heightleft, heightright);
	}
	
	int bfactor(node* t) {
		if (!t->right || !t->left) return 0;
		return t->right->height - t->left->height;
	}

	node* r_right(node* t);
	node* r_left(node* t);
	node* balance(node* t);

	node* getmin(node* t);
	node* deletemin(node* t);

	node* putnode(node* t, int value);
	void addnode(int value) { root = putnode(root, value); }
	node* deletenode(node* t, int value);
	void remove(int value) { root = deletenode(root, value); }

	void display();
};

void avl::inorder(node* t) {
	if (t) {
		inorder(t->left);
		std::cout << t->value << " ";
		inorder(t->right);
	}
}

void avl::preorder(node* t) {
	if (t) {
		std::cout << t->value << " ";
		preorder(t->left);
		preorder(t->right);
	}
}

void avl::postorder(node* t) {
	if (t) {
		postorder(t->left);
		postorder(t->right);
		std::cout << t->value << " ";
	}
}

void avl::itinorder(node* t) {
	stack<node*> s;
	node* temp = t;
	while (s.notempty() || temp) {
		if (temp) {
			s.push(temp);
			temp = temp->left;
		}
		else {
			temp = s.top();
			s.pop();
			std::cout << temp->value << " ";
			temp = temp->right;
		}
	}
}

void avl::itpreorder(node* t) {
	if (!t) return;

	stack<node*> s;
	s.push(t);

	while (s.notempty()) {
		node* temp = s.top();
		std::cout << temp->value << " ";
		s.pop();

		if (temp->left) s.push(temp->left);
		if (temp->right) s.push(temp->right);
	}
}

void avl::itpostorder(node* t) {
	if (!t) return;

	stack<node*> s;
	s.push(t);
	stack<int> out;

	while (s.notempty()) {
		node* temp = s.top();
		s.pop();

		out.push(temp->value);
		if (temp->left) s.push(temp->left);
		if (temp->right) s.push(temp->right);
	}

	while (out.notempty()) {
		std::cout << out.top() << " ";
		out.pop();
	}
}

void avl::levelorder(node* t) {
	if (!t) return;

	list<node*> queue;
	queue.addlastnode(t);

	node* temp = nullptr;

	while (queue.listsize()) {
		temp = queue.head->val;
		queue.deletenode();

		std::cout << temp->value << " ";

		if (temp->left) queue.addlastnode(temp->left);
		if (temp->right) queue.addlastnode(temp->right);
	}
}

node* avl::r_right(node* t) {
	node* temp = t->left;
	t->left = temp->right;
	temp->right = t;

	correctheight(t);
	correctheight(temp);

	return temp;
}

node* avl::r_left(node* t) {
	node* temp = t->left;
	temp->right = t->left;
	t->left = t;

	correctheight(t);
	correctheight(temp);

	return t;
}

node* avl::balance(node* t) {
	correctheight(t);

	if (bfactor(t) == 2) {
		if (bfactor(t->right) < 0) {
			t->right = r_right(t->right);
		}
		return r_left(t);
	}
	if (bfactor(t) == -2) {
		if (bfactor(t->left) > 0) {
			t->left = r_left(t->left);
		}
		return r_right(t);
	}
	return t;
}

node* avl::getmin(node* t) {
	if (!t->left) return t;
	return getmin(t->left);
}

node* avl::deletemin(node* t) {  
	if (!t->left) return t->right;

	t->left = deletemin(t->left);
	return t;
}

node* avl::putnode(node* t, int value) {
	if (!t) return new node(value);

	if (t->value > value) { t->left = putnode(t->left, value); }
	else if (t->value < value) { t->right = putnode(t->right, value); }
	else if (t->value == value) { t->value = value; }

	t->height = height(t->left) + height(t->right);

	return balance(t);
}

node* avl::deletenode(node* t, int value) {
	if (!t) return nullptr;

	if (t->value > value) { t->left = deletenode(t->left, value); }
	else if (t->value < value) { t->right = deletenode(t->right, value); }
	else {
		if (!t->right) return t->left;
		if (!t->left) return t->right;

		node* temp = t;
		t = getmin(temp->right);
		t->right = deletemin(temp->right);
		t->left = temp->left;

		return balance(t);
	}

	return balance(t);
}

void avl::display() {
	levelorder(root);
	std::cout << std::endl; 
}

int main() {
	int count;
	int range = 16384;
	avl q;
	
	std::cout << "Input the amount of tree elements: ";
	std::cin >> count;

	srand(time(NULL));
	for (int i = 0; i < count; i++) q.addnode(20 - i);//q.addnode((rand() % range) - (range / 2));
	
	q.display();

	return 0;
}
