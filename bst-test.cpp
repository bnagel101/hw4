#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    //Binary Search Tree tests
    // BinarySearchTree<char,int> bt;
    // bt.insert(std::make_pair('a',1));
    // bt.insert(std::make_pair('b',2));
    
    // cout << "Binary Search Tree contents:" << endl;
    // for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }
    // if(bt.find('b') != bt.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
    // cout << "Erasing b" << endl;
    // bt.remove('b');
    // bt.remove('c');
    // bt.remove('a');
    // bt.remove('h');
    // AVL Tree Tests
    // AVLTree<int, int> at;
    // at.insert(std::make_pair(10,1));
    // at.insert(std::make_pair(9,2));
    // at.insert(std::make_pair(30,3));
    // at.insert(std::make_pair(20,4));
    // at.insert(std::make_pair(31,5));
    // at.insert(std::make_pair(19,6));
		// at.insert(std::make_pair(32,7));
		// at.insert(std::make_pair(33,8));
		// at.insert(std::make_pair(34,9));
		// at.remove(20);
    cout << "\nAVLTree contents:" << endl;
    // for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }
    // if(at.find('b') != at.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
    // cout << "Erasing b" << endl;
    // at.remove('b');
    // AVLTree<int, int> at;
    // at.insert(std::make_pair(10,1));
		// at.remove(10);
	// 	AVLTree<int, int> testTree;

	// testTree.insert(std::make_pair(2, 8));
	// testTree.insert(std::make_pair(1, -50));
	// testTree.insert(std::make_pair(3, 0));
	// testTree.insert(std::make_pair(10, 0));
	// testTree.insert(std::make_pair(15, 0));

	// std::cout << "Before any removals, tree is: " << std::endl;
	// testTree.print();
	// testTree.remove(-1);
	// std::cout << "After removing -1 (which doesn't exist), tree is: " << std::endl;
	// testTree.print();
	// testTree.remove(2);
	// std::cout << "After removing 2 (the root), tree is: " << std::endl;
	// testTree.print();
	// testTree.remove(10);
	// std::cout << "After removing 10, tree is: " << std::endl;
	// testTree.print();
	// testTree.remove(1);

	// std::cout << "After removing 1, tree is: " << std::endl;
	// testTree.print();

	// testTree.remove(3);

	// std::cout << "After removing 3, tree is: " << std::endl;
	// testTree.print();

	// testTree.remove(15);

	// std::cout << "After removing 15 (the last element), tree is: " << std::endl;
	// testTree.print();

	// testTree.remove(15);

	// std::cout << "After removing 15 (which doesn't exist), tree is: " << std::endl;
	// testTree.print();
	AVLTree<int, double> bst;
	bst.insert(std::make_pair(-53, 1.0));
	bst.insert(std::make_pair(-73, 2.0));
	bst.insert(std::make_pair(50, 3.0));
	bst.insert(std::make_pair(-142, 4.0));
	bst.insert(std::make_pair(28, 5.0));
	bst.insert(std::make_pair(-64, 6.0));
	bst.insert(std::make_pair(106, 7.0));
	bst.insert(std::make_pair(2, 8.0));
	bst.insert(std::make_pair(75, 9.0));
	bst.insert(std::make_pair(147, 10.0));
	bst.insert(std::make_pair(-143, 11.0));
	bst.insert(std::make_pair(71, 12.0));
	bst.remove(-143);

  return 0;
}
