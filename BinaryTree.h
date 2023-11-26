#pragma once
#include <cassert>
#include <iostream>

using std::cout;
using std::endl;

template <typename K, typename V>
struct TreeNode
{
	K key;
	V value;
	TreeNode* children[2];
	TreeNode(K, V);
};

template <typename K, typename V>
class BinaryTree
{
private:
	TreeNode<K,V>* root = nullptr;
	void displayEntriesWorker(TreeNode<K, V>*);
	void displayTreeWorker(TreeNode<K, V>*, int);
	void deleteTreeWorker(TreeNode<K, V>*);
	void copyTreeWorker(TreeNode<K, V>*);
	void rotateLeft(TreeNode<K, V>*, TreeNode<K, V>*);
	void rotateRight(TreeNode<K, V>*, TreeNode<K, V>*);
public:
	BinaryTree();
	BinaryTree(BinaryTree<K, V>&);
	BinaryTree<K, V>& operator=(BinaryTree<K, V>&);
	BinaryTree(BinaryTree<K, V>&&);
	BinaryTree<K, V>& operator=(BinaryTree<K, V>&&);
	V* lookup(K);
	bool isTreeEmpty();
	void insert(K, V);
	void displayEntries();
	void displayTree();
	void remove(K);
	TreeNode<K, V>* getRoot();
	void deleteTree();
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Source code~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <typename K, typename V>
TreeNode<K, V>::TreeNode(K new_key, V new_value)
{
	key = new_key;
	value = new_value;
	children[0] = nullptr;
	children[1] = nullptr;
}

template <typename K, typename V>
BinaryTree<K, V>::BinaryTree() { root = nullptr; }

template <typename K, typename V>
BinaryTree<K, V>::BinaryTree(BinaryTree& treeToCopyFrom)
{
	//Called from either "BinaryTree tree1(tree2)" or "BinaryTree tree1 = tree2"
	if (treeToCopyFrom.root == nullptr) return;

	deleteTree();
	copyTreeWorker(treeToCopyFrom.root);
}

template <typename K, typename V>
BinaryTree<K, V>& BinaryTree<K, V>::operator=(BinaryTree& treeToCopyFrom)
{
	//Called from "tree1 = tree2" where tree1 is already defined
	if (treeToCopyFrom.root == nullptr) return treeToCopyFrom;

	deleteTree();
	copyTreeWorker(treeToCopyFrom.root);
	return *this;
}

template <typename K, typename V>
void BinaryTree<K, V>::copyTreeWorker(TreeNode<K, V>* node)
{
	insert(node->key, node->value);
	if (node->children[0] != nullptr) copyTreeWorker(node->children[0]);
	if (node->children[1] != nullptr) copyTreeWorker(node->children[1]);
}

template <typename K, typename V>
BinaryTree<K, V>::BinaryTree(BinaryTree&& oldTree)
{
	//Called with "BinaryTree tree1(std::move(tree2))" or "BinaryTree tree1 = std::move(tree2)"
	if (this->root == oldTree.root) return;

	deleteTree();
	root = oldTree.getRoot();
	oldTree.root = nullptr;
}

template <typename K, typename V>
BinaryTree<K, V>& BinaryTree<K, V>::operator=(BinaryTree&& oldTree)
{
	//Called with "tree1 = std::move(tree2)" where tree1 is already defined
	if (this->root == oldTree.root) return oldTree;

	deleteTree();
	root = oldTree.getRoot();
	oldTree.root = nullptr;
	return *this;
}

template <typename K, typename V>
TreeNode<K, V>* BinaryTree<K, V>::getRoot() { return this->root; }

template <typename K, typename V>
bool BinaryTree<K, V>::isTreeEmpty() { return this->root == nullptr; }

template <typename K, typename V>
V* BinaryTree<K, V>::lookup(K key)
{
	if (root == nullptr) return nullptr;
	TreeNode<K, V>* current = root; bool finding = true;
	while (finding) {
		if (current->key == key) return &current->value;
		else {
			int side = current->key < key;
			if (current->children[side] != nullptr) {
				current = current->children[side];
			} else {
				return nullptr;
			}
		}
	} throw std::exception("Last line of BinaryTree::lookup()");
}

template <typename K, typename V>
void BinaryTree<K, V>::insert(K key, V value)
{
	if (root == nullptr) {
		TreeNode<K, V>* new_TreeNode = new TreeNode<K, V>(key, value);
		root = new_TreeNode;
		return;
	}
	TreeNode<K, V>* current = root;
	bool finding = true;
	while (finding) {
		if (current->key == key) {
			current->value = value;
			return;
		} else {
			int side = current->key < key;
			if (current->children[side] == nullptr) {
				TreeNode<K, V>* new_TreeNode = new TreeNode<K, V>(key, value);
				current->children[side] = new_TreeNode;
				return;
			} else {
				current = current->children[side];
			}
		}
	}
}

template <typename K, typename V>
void BinaryTree<K, V>::remove(K key)
{
	TreeNode<K, V>* current = root; bool finding = true;
	TreeNode<K, V>* node = nullptr; TreeNode<K, V>* parentNode = nullptr;
	while (finding) {
		if (current->key == key) {
			node = current;
			finding = false;
		} else {
			int side = current->key < key;
			if (current->children[side] != nullptr) {
				parentNode = current;
				current = current->children[side];
			} else {
				return;
			}
		}
	}

	bool condL = node->children[0] == nullptr;
	bool condR = node->children[1] == nullptr;
	if (condL && condR) { //If no children
		if (parentNode == nullptr) {
			root = nullptr;
		} else if (parentNode->children[0] == node) {
			parentNode->children[0] = nullptr;
		} else {
			parentNode->children[1] = nullptr;
		}
	} else if (condL || condR) { //If one child
		if (parentNode == nullptr) {
			int side = condL;
			root = node->children[side];
		} else {
			int side1 = parentNode->children[1] == node;
			int side2 = condL;
			parentNode->children[side1] = node->children[side2];
		}
	} else { //If 2 children
		TreeNode<K, V>* newNode = node->children[1]; TreeNode<K, V>* aboveNewNode = nullptr;
		while (newNode->children[0] != nullptr) {
			//Tries to find the innermost node on the newNode's left
			aboveNewNode = newNode;  //Original parent of newNode
			newNode = newNode->children[0];
		}
		if (aboveNewNode != nullptr) {
			aboveNewNode->children[0] = newNode->children[1];
			newNode->children[1] = node->children[1];
		}
		newNode->children[0] = node->children[0];
		if (node != root) {
			int replaceSide = parentNode->children[1] == node;
			parentNode->children[replaceSide] = newNode;
		} else {
			root = newNode;
		}
	}
	delete node;
}

template <typename K, typename V>
void BinaryTree<K, V>::displayEntries()
{
	if (root != nullptr) displayEntriesWorker(root);
}

template <typename K, typename V>
void BinaryTree<K, V>::displayEntriesWorker(TreeNode<K, V>* node)
{
	//This is in-order traversal.
	if (node->children[0] != nullptr) displayEntriesWorker(node->children[0]);
	cout << node->key << " " << node->value << endl;
	if (node->children[0] != nullptr) displayEntriesWorker(node->children[1]);
}

template <typename K, typename V>
void BinaryTree<K, V>::displayTree()
{
	if (root != nullptr) displayTreeWorker(root, 0);
}

template <typename K, typename V>
void BinaryTree<K, V>::displayTreeWorker(TreeNode<K, V>* node, int level)
{
	//This is in-order traversal
	if (node->children[0] != nullptr) displayTreeWorker(node->children[0], level + 1);
	int i; for (i = 0; i < level; i++) { cout << "  "; }
	cout << node->key << " " << node->value << endl;
	if (node->children[1] != nullptr) displayTreeWorker(node->children[1], level + 1);
}

template <typename K, typename V>
void BinaryTree<K, V>::deleteTree()
{
	if (root != nullptr) deleteTreeWorker(root);
	root = nullptr;
}

template <typename K, typename V>
void BinaryTree<K, V>::deleteTreeWorker(TreeNode<K, V>* node)
{
	//This is post-order traversal
	if (node->children[0] != nullptr) deleteTreeWorker(node->children[0]);
	if (node->children[1] != nullptr) deleteTreeWorker(node->children[1]);
	//cout << "~~Deleting node " << node->key << endl;
	delete node;
}

template <typename K, typename V>
void BinaryTree<K, V>::rotateLeft(TreeNode<K, V>* node, TreeNode<K, V>* parent)
{
	TreeNode<K, V>* newRoot = node->children[1];       //Constant

	assert(isTreeEmpty() || newRoot == nullptr); //Constant

	if (parent == nullptr) {                     //Constant
		root = newRoot;                          //Constant
	} else {
		int side = parent->key < node->key;      //Constant
		parent->children[side] = newRoot;        //Constant
	}
	node->children[1] = newRoot->children[0];    //Constant
	newRoot->children[0] = node;                 //Constant
}

template <typename K, typename V>
void BinaryTree<K, V>::rotateRight(TreeNode<K, V>* node, TreeNode<K, V>* parent)
{
	TreeNode<K, V>* newRoot = node->children[0];       //Constant

	assert(isTreeEmpty() || newRoot == nullptr); //Constant

	if (parent == nullptr) {                     //Constant
		root = newRoot;                          //Constant
	} else {
		int side = parent->key < node->key;      //Constant
		parent->children[side] = newRoot;        //Constant
	}
	node->children[0] = newRoot->children[1];    //Constant
	newRoot->children[1] = node;                 //Constant
}