/*
 * BinarySearchTree.h
 *
 *  Created on: Apr 27, 2020
 *      Author: Minh Tran
 */

#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include<iostream>
#include<queue>
using namespace std;

struct Node {
	int val;
	Node* left;
	Node* right;
	Node(int x) {
		val = x;
		left = right = NULL;
	}
};

class BinarySearchTree {
private:
	Node * root;
	int countNodes(Node *p);
	int countLeaf(Node *p);
	int max(int x, int y);
	int countHeight(Node *p);
	void destroy(Node * p);
	void deleteFromTree(Node *&p);
	void searchTree(Node *p, int val);
	void inorder(Node *p);
	void preorder(Node *p);
	void postorder(Node *p);
	void BFS(Node * p);
public:
	BinarySearchTree();
	int getNodesCount();
	int getLeavesCount();
	int getTreeHeight();
	bool isEmpty();
	void insertNode(int val);
	void deleteNode(int val);
	void searchNode(int val);
	void inorderTraversal();
	void postorderTraversal();
	void preorderTraversal();
	void BFSTraversal();
	~BinarySearchTree();
};

// Default constructor
BinarySearchTree::BinarySearchTree() {
	root = NULL;
}

int BinarySearchTree::getNodesCount() {
	return countNodes(root);
}

int BinarySearchTree::countNodes(Node * p) {
	if (p == NULL) {
		return 0;
	} else {
		return 1 + countNodes(p->left) + countNodes(p->right);
	}
}

int BinarySearchTree::getLeavesCount() {
	return countLeaf(root);
}

int BinarySearchTree::countLeaf(Node * p) {
	if (p == NULL) {
		return 0;
	} else if (p->left == NULL && p->right == NULL) {
		return 1;
	} else {
		return countLeaf(p->left) + countLeaf(p->right);
	}
}

int BinarySearchTree::getTreeHeight() {
	return countHeight(root);
}

int BinarySearchTree::countHeight(Node * p) {
	if (p == NULL) {
		return 0;
	} else {
		return 1 + max(countHeight(p->left), countHeight(p->right));
	}
}

int BinarySearchTree::max(int x, int y) {
	if (x > y) {
		return x;
	}
	return y;
}

bool BinarySearchTree::isEmpty() {
	return (root == NULL);
}

void BinarySearchTree::insertNode(int val) {
	Node* newNode = new Node(val);
	Node* currentNode;
	Node* trailNode;

	if (root == NULL) {
		root = newNode;
	} else {

		currentNode = root;

		while (currentNode != NULL) {

			trailNode = currentNode;

			if (val == currentNode->val) {
				cout << val
						<< " is already in the tree. Duplicates are not allowed.\n";
				return;
			} else if (val > currentNode->val) {
				currentNode = currentNode->right;
			} else {
				currentNode = currentNode->left;
			}
		}

		if (val > trailNode->val) {
			trailNode->right = newNode;
		} else {
			trailNode->left = newNode;
		}
	}
	cout << newNode->val << " has been inserted into the tree.\n";
}

void BinarySearchTree::deleteNode(int val) {
	Node * current;
	Node * trailCurrent;
	bool found = false;

	if (root == NULL) {
		cout << "Tree is empty.\n";
		return;
	} else {

		current = root;
		trailCurrent = root;

		while (current != NULL && !found) {

			if (val == current->val) {
				found = true;
			} else {
				trailCurrent = current;
				if (val < current->val) {
					current = current->left;
				} else {
					current = current->right;
				}
			}

		}

		if (current == NULL) {
			cout << val << " is not in the tree.\n";
		} else if (found) {
			if (current == root) {
				deleteFromTree(root);
			} else if (trailCurrent->val > val) {
				deleteFromTree(trailCurrent->left);
			} else {
				deleteFromTree(trailCurrent->right);
			}
		}
	}
}

void BinarySearchTree::deleteFromTree(Node * &p) {
	Node * temp;
	Node * current;
	Node * trailCurrent;

	if (p == NULL) {
		cerr << "Error: The node to be deleted is NULL.\n";
	} else if (p->left == NULL && p->right == NULL) {
		temp = p;
		p = NULL;
		cout << temp->val << " has been deleted.\n";
		delete temp;
	} else if (p->left == NULL) {
		temp = p->right;
		p = NULL;
		cout << temp->val << " has been deleted.\n";
		delete temp;
	} else if (p->right == NULL) {
		temp = p->left;
		p = NULL;
		cout << temp->val << " has been deleted.\n";
		delete temp;
	} else {
		current = p->left;
		trailCurrent = NULL;

		while (current->right != NULL) {
			trailCurrent = current;
			current = current->right;
		}

		cout << p->val << " has been deleted.\n";
		p->val = current->val;

		if (trailCurrent == NULL)
			p->left = current->left;
		else
			trailCurrent->right = current->left;

		delete current;
	}
}

void BinarySearchTree::searchNode(int val) {
	searchTree(root, val);
}

void BinarySearchTree::searchTree(Node *p, int val) {
	Node * current;
	Node * trailCurrent;
	bool found = false;
	int level = 1;

	current = root;
	trailCurrent = root;

	while (current != NULL && !found) {
		trailCurrent = current;

		if (val == current->val) {
			found = true;
		} else if (val < current->val) {
			current = current->left;
			++level;
		} else {
			current = current->right;
			++level;
		}
	}

	if (current == NULL) {
		cout << val << " is not in the tree.\n";
	} else if (found) {
		cout << trailCurrent->val << " is on level " << level << ".";
	}
}

void BinarySearchTree::inorderTraversal() {
	cout << "Inorder traversal: ";
	inorder(root);
	cout << endl;
}

void BinarySearchTree::preorderTraversal() {
	cout << "Preorder traversal: ";
	preorder(root);
	cout << endl;
}

void BinarySearchTree::postorderTraversal() {
	cout << "Postorder traversal: ";
	postorder(root);
	cout << endl;
}

void BinarySearchTree::inorder(Node * p) {
	if (p != NULL) {
		inorder(p->left);
		cout << p->val << " ";
		inorder(p->right);
	}
}

void BinarySearchTree::preorder(Node * p) {
	if (p != NULL) {
		cout << p->val << " ";
		preorder(p->left);
		preorder(p->right);
	}
}

void BinarySearchTree::postorder(Node * p) {
	if (p != NULL) {
		postorder(p->left);
		postorder(p->right);
		cout << p->val << " ";
	}
}

void BinarySearchTree::BFSTraversal() {
	BFS(root);
}

void BinarySearchTree::BFS(Node * p) {
	queue<Node *> myQueue;

	cout << "BFS traversal: ";
	myQueue.push(p);
	while (!myQueue.empty()) {
		Node * temp = myQueue.front();
		cout << temp->val << " ";
		myQueue.pop();

		if (temp->left != NULL) {
			myQueue.push(temp->left);
		}
		if (temp->right != NULL) {
			myQueue.push(temp->right);
		}
	}
	cout << endl;
}

BinarySearchTree::~BinarySearchTree() {
	destroy(root);
}

void BinarySearchTree::destroy(Node * p) {
	while (p != NULL) {
		destroy(p->left);
		destroy(p->right);
		delete p;
		p = NULL;
	}
}

#endif /* BINARYSEARCHTREE_H_ */
