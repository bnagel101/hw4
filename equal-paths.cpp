#include "equal-paths.h"
using namespace std;
#include <algorithm>

// You may add any prototypes of helper functions here

int calculateHeightIfBalanced(Node * root){
    if(root == nullptr){
        return 0;
    }
    return 1 + std::max(calculateHeightIfBalanced(root->left), calculateHeightIfBalanced(root->right));
}

bool isBalanced(Node * root){
	if(root == nullptr){
		return true;
	}
	if(root->left == nullptr && root->right == nullptr){
		return true;
	}else{
		return false;
	}
}

bool equalPaths(Node * root)
{
    // base case of recursive
	if(root == nullptr){
		return true;
	}
	else if(root->right != nullptr ^ root->left != nullptr){
		if(isBalanced(root->right) && isBalanced(root->left)){
			return true;
		}	
	}
	else{
		if(calculateHeightIfBalanced(root->left) - calculateHeightIfBalanced(root->right) == 0){
			return true;
		}else{
			return false;
		}
	}
}

