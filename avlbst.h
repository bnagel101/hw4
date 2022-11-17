#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"
#include "print_bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap(AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void rightSwap(AVLNode<Key,Value>* node);
    void leftSwap(AVLNode<Key,Value>* node);
    void balanceNode(AVLNode<Key,Value>* node);
    void properRotation(AVLNode<Key,Value>* node);
    AVLNode<Key,Value>* lazyInsertBstHelper(const std::pair<const Key, Value> &new_item);
		AVLNode<Key,Value>* lazyRemoveBstHelper(const Key& key);
		void balanceAll(AVLNode<Key,Value>* root);
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */

template<class Key, class Value>
void AVLTree<Key, Value>::balanceAll(AVLNode<Key,Value>* root){
	//recursive function to go through entire tree and check for unbalanced nodes
	if(root == nullptr){
		return;
	}else{
		balanceAll(root->getLeft());
		balanceAll(root->getRight());
		balanceNode(root);
		if(root->getBalance() < (int8_t)(-1) || root->getBalance() > (int8_t)(1)){
			properRotation(root);
		}
	}
}

template<class Key, class Value>
void AVLTree<Key, Value>::balanceNode(AVLNode<Key,Value>* node){
	//function for auto balancing node
    if(node == nullptr){
        return;
    }
    int8_t b = (int8_t)(BinarySearchTree<Key, Value>::calculateHeightIfBalanced(node->getLeft()) - BinarySearchTree<Key, Value>::calculateHeightIfBalanced(node->getRight()));
    node->setBalance(b);
}

template<class Key, class Value>
void AVLTree<Key, Value>::leftSwap( AVLNode<Key,Value>* node){
		//checks if node is a root
		bool r = false;
		if(BinarySearchTree<Key, Value>::root_ == static_cast<Node<Key,Value>*>(node)){
			r = true;
		}
    AVLNode<Key, Value>* rc = node->getRight();
    AVLNode<Key, Value>* rlc = rc->getLeft();
		bool nodeIsLeft = false;
		//need to find out wether node is a left child or right child
		if(node->getParent() != nullptr && (node == node->getParent()->getLeft())){
				nodeIsLeft = true;
		}
    rc->setLeft(node);
    rc->setParent(node->getParent());
		if(nodeIsLeft){
			node->getParent()->setLeft(rc);
		}else if(node->getParent() != nullptr){
			node->getParent()->setRight(rc);
		}
    node->setParent(rc);
    node->setRight(rlc);
    if(rlc != nullptr){
        rlc->setParent(node);
    }
    balanceNode(node);
    balanceNode(rc);
    balanceNode(rlc);
		//if node was root need to update root data member
		if(r){
			BinarySearchTree<Key, Value>::root_ = rc;
		}

}

template<class Key, class Value>
void AVLTree<Key, Value>::rightSwap(AVLNode<Key,Value>* node){
		bool r = false;
		if(BinarySearchTree<Key, Value>::root_ == static_cast<Node<Key,Value>*>(node)){
			r = true;
		}
    AVLNode<Key, Value>* lc = node->getLeft();
    AVLNode<Key, Value>* lrc = lc->getRight();
		bool nodeIsLeft = false;
		//need to find out whether node is a left child or right child
		if(node->getParent() != nullptr && (node == node->getParent()->getLeft())){
				nodeIsLeft = true;
		}
		//updating placement of left child by seting right child to node and setting parent to parent of node
		
    lc->setRight(node);
    lc->setParent(node->getParent());
		//also need to set child of parent of node to left child
		if(nodeIsLeft){
			node->getParent()->setLeft(lc);
		}else if(node->getParent() != nullptr){
			node->getParent()->setRight(lc);
		}
		//update parent of node to left child and set left child of node to the right child of the left child
    node->setParent(lc);
    node->setLeft(lrc);
    if(lrc != nullptr){
        lrc->setParent(node);
    }
		//update balance of nodes
    balanceNode(node);
    balanceNode(lc);
    balanceNode(lrc);
		//if root then update the root data member
		if(r){
			BinarySearchTree<Key, Value>::root_ = lc;
		}

}
template<class Key, class Value>
void AVLTree<Key, Value>::properRotation(AVLNode<Key,Value>* node){
    //doing proper roation for unbalanced node
    if(node == nullptr){
        return;
    }
		
    AVLNode<Key,Value>* rc = node->getRight();
    AVLNode<Key,Value>* lc = node->getLeft();
		balanceNode(rc);
		balanceNode(lc);
    //right right swap first
    if(node->getBalance() < -1 && rc != nullptr && (rc->getBalance() < 0 || rc->getBalance() == 0)){
        leftSwap(node);
    //right left rotation check
    }else if(node->getBalance() < -1 && rc != nullptr && rc->getBalance() > 0){
        rightSwap(rc);
        leftSwap(node);
    //left left rotation check
    }else if(node->getBalance() > 1 && lc != nullptr && (lc->getBalance() > 0 || lc->getBalance() == 0)){
        rightSwap(node);
    //left right rotation check
    }else if(node->getBalance() > 1 && lc != nullptr && lc->getBalance() < 0){
        leftSwap(lc);
        rightSwap(node);
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    Node<Key, Value>* base = BinarySearchTree<Key, Value>::internalFind(new_item.first);
    if(base != nullptr){
        base->setValue(new_item.second);
        return;
    }
    //insert into tree with standard bst insertion
    
    AVLNode<Key, Value>* above = lazyInsertBstHelper(new_item);
    balanceNode(above);
    //find the first unbalanced node going up from the newly inserted node
    while(above != nullptr){
        balanceNode(above);
        if(above->getBalance() < (int8_t)(-1) || above->getBalance() > (int8_t)(1)){
            break;
        }
        above = above->getParent();
    }
    properRotation(above);
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    // TODO
		AVLNode<Key,Value>* node = lazyRemoveBstHelper(key);
		balanceNode(node);
		
		//find the first unbalanced node going up from the newly removed node
    while(node != NULL){
        balanceNode(node);
        if(node->getBalance() < (int8_t)(-1) || node->getBalance() > (int8_t)(1)){
            break;
        }
        node = node->getParent();
    }

		properRotation(node);
		//i had a case where it didn't pick up on which node was balanced incorrectly
		//so i just wrote a recursive function that goes through the entire tree and finds
		//node that are unbalanced and then does the proper rotation
		balanceAll(static_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key, Value>::root_));
		//this->printRoot(BinarySearchTree<Key, Value>::root_);
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
		balanceNode(n1);
		balanceNode(n2);
}



template<class Key, class Value>
AVLNode<Key,Value>* AVLTree<Key, Value>::lazyInsertBstHelper(const std::pair<const Key, Value> &keyValuePair){
	//copy and pasted insert function from bst but changes nodes to new avl nodes and made it return a node
    Key k = keyValuePair.first;
    Value val = keyValuePair.second;
    //check if empty bc might have to set root to new node
    if(BinarySearchTree<Key, Value>::empty()){
        BinarySearchTree<Key, Value>::root_ = new AVLNode<Key, Value>(k, val, nullptr);
				return  static_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key, Value>::root_);
    }
    Node<Key, Value>* temp = BinarySearchTree<Key, Value>::root_;
    AVLNode<Key, Value>* newN = new AVLNode<Key, Value>(k, val, static_cast<AVLNode<Key,Value>*>(temp));
    while(temp != nullptr){
        Key rk = temp->getKey();
        if(k < rk){
            //if no children set new node as left child, else continue to left
            if(temp->getLeft() == nullptr){
                temp->setLeft(newN);
                newN->setParent(temp);
                return newN;
            }else{
                temp = temp->getLeft();
            }
            //if equal overwrite current value
        }else if(k == rk){
            temp->setValue(val);
            return newN;
        }else{
            if(temp->getRight() == nullptr){
                temp->setRight(newN);
                newN->setParent(temp);
                return newN;
            }else{
                temp = temp->getRight();
            }
        }
    }
    return nullptr;
}

template<class Key, class Value>
AVLNode<Key,Value>* AVLTree<Key, Value>::lazyRemoveBstHelper(const Key& key){
	//copy and pasted remove function from bst but changes nodes to new avl nodes and made it return a node 
	AVLNode<Key, Value>* temp = static_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key, Value>::internalFind(key));
	AVLNode<Key, Value>* replace = nullptr;
	if(temp == nullptr){
			return replace;
	}
	AVLNode<Key,Value>* pred = static_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key, Value>::predecessor(temp));
	//if node has two children do the swap
	if(temp->getLeft() != nullptr && temp->getRight() != nullptr){
		nodeSwap(pred, temp);
	}
	//check and see if node is a left child or right child
	AVLNode<Key, Value>* tempP = temp->getParent();
	bool tempIsLeft = false;
	//need to find out wether node is a left child or right child
	if(temp->getParent() != nullptr && (temp == temp->getParent()->getLeft())){
			tempIsLeft = true;
	}
	
	//if left child exists, promote child by changing parent
	if(temp->getLeft() != nullptr){
		AVLNode<Key, Value>* temp2 = temp->getLeft();
		temp2->setParent(temp->getParent());
		if(tempIsLeft){
				tempP->setLeft(temp2);
		}else if(tempP != nullptr && !tempIsLeft){
				tempP->setRight(temp2);
		}else{
			BinarySearchTree<Key, Value>::root_ = temp2;
			
		}
		delete temp;
		replace = temp2;
	}
    //if right child exists, promote child by settting parent of child to parent of 
    //node being removed, then using tempIsLeft variable change the child of the parent
    //node to be the child of the node being removed
	else if(temp->getRight() != nullptr){
		AVLNode<Key, Value>* temp2 = temp->getRight();
		temp2->setParent(temp->getParent());
		if(tempIsLeft){
				tempP->setLeft(temp2);
		}else if(tempP != nullptr && !tempIsLeft){
				tempP->setRight(temp2);
		}else{
			BinarySearchTree<Key, Value>::root_ = temp2;
		}
		delete temp;
		replace = temp2;
	}
	else {
		if(tempIsLeft){
				tempP->setLeft(NULL);
		}else if(tempP != NULL && !tempIsLeft){
				tempP->setRight(NULL);
		}else{
			BinarySearchTree<Key, Value>::root_ = nullptr;
		}
		delete temp;
		replace = tempP;
	}
	return replace;
}

#endif
