#pragma once
#include <functional>
#include <iostream>

using std::cout;
using std::endl;

template <typename V>
struct ListNode {
	V value;
	ListNode* next;
	ListNode(V);
};

template <typename V>
class SLList 
{
private:
	ListNode<V>* root = nullptr;
	ListNode<V>* getRoot();
	void copyListWorker(ListNode<V>*);
	V* atWorker(ListNode<V>*, int);
	int searchWorker(ListNode<V>*, int, V);
	void insertWorker(ListNode<V>*, int, V);
	void displayAllWorker(ListNode<V>*);
	ListNode<V>* removeWorker(ListNode<V>*, int);
	ListNode<V>* removeIfWorker(ListNode<V>*, std::function<bool(int)>, int);
	void deleteListWorker(ListNode<V>*);
public:
	SLList();
	SLList(V[]);
	SLList(SLList<V>&);
	SLList& operator=(SLList<V>&);
	SLList(SLList<V>&&);
	SLList& operator=(SLList<V>&&);
	int length();
	V* at(int);
	V* operator[](int);
	int search(V);
	bool empty();
	void insert(int, V);
	void push_front(V);
	void push_back(V);
	void displayAll();
	void remove(int);
	void removeIf(std::function<bool(int)>);
	void pop_front();
	void pop_back();
	void deleteList();
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Source code~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <typename V>
ListNode<V>::ListNode(V new_value) {
	value = new_value;
	next = nullptr;
}

template <typename V>
SLList<V>::SLList() { root = nullptr; }

template <typename V>
SLList<V>::SLList(V input_array[]) {
	if (input_array.empty()) { root = nullptr; return; }
	root = new ListNode(input_array[0]);
	ListNode* current = root;
	for (int i = 1; i < input_array.length(); i++) {
		current->next = new ListNode * (input_array[i]);
		current = current->next;
	}
}

template <typename V>
SLList<V>::SLList(SLList& new_list) {
	//Called from either "SLList list1(list2)" or "SLList list1 = list2"
	if (new_list.empty()) return;
	deleteList();
	copyListWorker(new_list.root, new_list);
}

template <typename V>
SLList<V>& SLList<V>::operator=(SLList& new_list) {
	//Called from "list1 = list2" where list1 is already defined
	if (new_list.empty()) return;
	deleteList();
	copyListWorker(new_list.root);
}

template <typename V>
void SLList<V>::copyListWorker(ListNode<V>* node) {
	insert(node->key, node->value);
	if (node->next != nullptr) copyListWorker(node->next);
}

template <typename V>
SLList<V>::SLList(SLList&& oldList) {
	//Called with "SLList list1(std::move(list2))" or "SLList list1 = std::move(list2)"
	if (oldList.empty()) return;
	deleteList();
	root = oldList.getRoot();
	oldList.root = nullptr;
}

template <typename V>
SLList<V>& SLList<V>::operator=(SLList<V>&& oldList) {
	//Called with "tree1 = std::move(tree2)" where tree1 is already defined
	if (oldList.empty()) return;
	deleteList();
	root = oldList.getRoot();
	oldList.root = nullptr;
}

template <typename V>
ListNode<V>* SLList<V>::getRoot() { return this->root; }

template <typename V>
int SLList<V>::length() {
	int count = 0;
	ListNode<V>* current = root;
	while (current != nullptr) { count++; current = current->next; } 
	return count;
}

template <typename V>
V* SLList<V>::at(int index) {
	if (root == nullptr || index < 0) return nullptr;
	return atWorker(root, index);
}

template <typename V>
V* SLList<V>::operator[](int index) {
	if (root == nullptr || index < 0) return nullptr;
	return atWorker(root, index);
}

template <typename V>
V* SLList<V>::atWorker(ListNode<V>* node, int index) {
	if (index == 0) return &node->value; //If at the index
	if (node->next == nullptr) return nullptr;  //If at the end of the list
	else return atWorker(node->next, index - 1);
}

template <typename V>
int SLList<V>::search(V value) {
	if (root == nullptr) return -1;
	return searchWorker(root, value);
}

template <typename V>
int SLList<V>::searchWorker(ListNode<V>* node, int index, V value) {
	if (node->value == value) return index;
	if (node->next == nullptr) return -1;
	return searchWorker(node->next, index + 1, value);
}

template <typename V>
bool SLList<V>::empty() { return this->root == nullptr; }

template <typename V>
void SLList<V>::insert(int index, V value) {
	if (root == nullptr) {
		if (index == 0) root = new ListNode<V>(value);
		else throw std::exception("SLList error on insert(). Index out of range");
	} else { insertWorker(root, index, value); }
}

template <typename V>
void SLList<V>::insertWorker(ListNode<V>* node, int index, V value) {
	if (index == 0) node->next = new ListNode<V>(value);
	else if (node->next == nullptr) throw std::exception("SLList error on insert(). Index out of range");
	else insertWorker(node->next, index - 1, value);
}

template <typename V>
void SLList<V>::push_front(V value) {
	if (root == nullptr) { root = new ListNode<V>(value); return; }
	ListNode<V>* old_root = root;
	root = new ListNode<V>(value);
	root->next = old_root;
}

template <typename V>
void SLList<V>::push_back(V value) {
	if (root == nullptr) { root = new ListNode<V>(value); return; }
	ListNode<V>* current = root;
	while (current->next != nullptr) current = current->next;
	current->next = new ListNode<V>(value);
}

template <typename V>
void SLList<V>::displayAll() {
	if (root == nullptr) {
		cout << "This list is empty.";
	} else {
		cout << "(";
		displayAllWorker(root);
		cout << ")";
	} 
}

template <typename V>
void SLList<V>::displayAllWorker(ListNode<V>* node) {
	cout << node->value;
	if (node->next != nullptr) {
		cout << " , ";
		displayAllWorker(node->next);
	}
}

template <typename V>
void SLList<V>::remove(int index) {
	if (root == nullptr) throw std::exception("SLList error. on remove() Cannot remove on empty list.");
	root = removeWorker(root, index);
}

template <typename V>
ListNode<V>* SLList<V>::removeWorker(ListNode<V>* node, int index) {
	if (node->next == nullptr) throw std::exception("SLList error on remove(). Index out of range.");
	if (index == 0) {
		//If index == 0, remove this node and return the index after 
		ListNode<V>* new_next = node->next;
		delete node;
		return new_next;
	} else { node->next = removeWorker(node->next, index - 1); }
}

template <typename V>
void SLList<V>::removeIf(std::function<bool(int)> compare) {
	if (root == nullptr) throw std::exception("SLList error. on removeIf() Cannot remove on empty list.");
	root = removeIfWorker(root, compare, 0);
}

template <typename V>
ListNode<V>* SLList<V>::removeIfWorker(ListNode<V>* node, std::function<bool(int)> compare, int index) {
	if (node == nullptr) return nullptr; //Reached the last node in the list
	node->next = removeIfWorker(node->next, compare, index + 1); //Go to the very end and work backwards
	if (compare(index)) {
		ListNode<V>* new_next = node->next;
		delete node;
		return new_next; //If removal, then save the next, deallocate the current memory, and return the saved next as the new next of the previous node
	} else { return node; } //If no removal, then return the current node as the next of the previous 
}

template <typename V>
void SLList<V>::pop_front() {
	if (root == nullptr) throw std::exception("SLList error. on pop_front() Cannot remove on empty list.");
	ListNode* old_root = root;	//Save the address of the root
	root = root->next;			//Remove root node from list
	delete old_root;			//Deallocate old root node
}

template <typename V>
void SLList<V>::pop_back() {
	if (root == nullptr) throw std::exception("SLList error. on pop_back() Cannot remove on empty list.");
	ListNode* current = root;
	if (current->next == nullptr) { //If there is only one node
		delete current;
		root = nullptr;
		return;
	}
	while (current->next->next == nullptr) current = current->next;
	ListNode* old_end = current->next;
	current->next = nullptr;
	delete old_end;
}

template <typename V>
void SLList<V>::deleteList() {
	if (root == nullptr) return;
	deleteListWorker(root);
	delete root;
	root = nullptr;
}

template <typename V>
void SLList<V>::deleteListWorker(ListNode<V>* node) {
	if (node == nullptr) return; //Nothing to remove here
	deleteListWorker(node->next); //Go to next node
	delete node; //This will only start deallocating when you reach the last node and then it'll work backwards.
}