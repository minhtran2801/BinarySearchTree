#include <iostream>
#include "BinarySearchTree.h"
using namespace std;

int main() {
	BinarySearchTree tree;
	tree.insertNode(100);
	tree.insertNode(200);
	tree.insertNode(300);
	tree.insertNode(20);
	tree.insertNode(10);
	tree.insertNode(30);
	tree.insertNode(150);

	cout << endl;
	cout << "Leaves num: " << tree.getLeavesCount();
	cout << "\nNodes num: " << tree.getNodesCount();
	cout << "\nHeight: " << tree.getTreeHeight() << endl;

	cout << endl;
	tree.deleteNode(200);
	tree.deleteNode(1);
	tree.deleteNode(30);

	cout << endl << "DFS traversal:\n";
	tree.inorderTraversal();
	tree.preorderTraversal();
	tree.postorderTraversal();

	cout << endl;
	tree.BFSTraversal();

	cout << endl;
	tree.searchNode(0);
	tree.searchNode(150);
	cout << endl;

	return 0;
}
