#include "RBTree.hpp"

int main()
{
	ft::RBTree< int, int > bst;
	bst.insert(8);
	bst.insert(18);
	bst.insert(5);
	bst.insert(15);
	bst.insert(17);
	bst.insert(25);
	bst.insert(40);
	bst.insert(80);
	bst.insert(3);
	bst.insert(10);
	bst.prettyPrint();
	bst.deleteNode(25);
	bst.deleteNode(5);
	bst.deleteNode(17);
	bst.deleteNode(18);
	bst.deleteNode(80);
	bst.deleteNode(3);
	bst.deleteNode(40);
	bst.deleteNode(8);
	bst.deleteNode(15);
	bst.deleteNode(10);
	bst.deleteNode(10);
	bst.prettyPrint();
	bst.freeNodes(bst.getRoot());
	return 0;
}