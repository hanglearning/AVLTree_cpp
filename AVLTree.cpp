/* 11/10/17
 * This file is the definition file of AVLTree 
*/
#include "AVLTree.hpp"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstring>
using namespace std;

AVLTree::AVLTree(bool flag){
	root = NULL;
	AVLflag = flag;
}

/* This function finds the node with word by recursion */
bool AVLTree::findWord(string s, NodeT *r){ //call with root as *r
	if (r == NULL){
		return false;
	}
	if (r->word == s){
		return true;
	}
	if (strcmp(s.c_str(),r->word.c_str()) <= 0){
		return findWord(s, r->left); //why if I don't write return here it says out of the control?
	} else {
		return findWord(s, r->right);
	}
}

/*This method is the brain and coordinator of modifying the tree,
 It will first add the node to its correct position based on the
 property of BST, and call adjustHeights() to update the hight of the
 nodes in the tree. adjustHeights() will update the heights accordingly
 by if it's an AVL tree or not.
 */
void AVLTree::addNode(string s){
    if (root == NULL){
        cout <<"Made root"<<endl;
        root = new NodeT(s);
        root->height++;
        return;
    } else {
        NodeT *tmp = root;
        while (tmp != NULL){
            if (strcmp(s.c_str(),tmp->word.c_str()) <= 0){
                // go to left subtree
                if (tmp->left != NULL){
                    //No insertion, keep looking
                    cout <<"Looking left of "<<tmp->word<<endl;
                    tmp = tmp->left;
                } else {
                    //If empty, insert here
                    cout<<"Inserting to left of "<<tmp->word<<endl;
                    tmp->left = new NodeT(s);
                    tmp->left->parent = tmp; // you got know your parent kid!
                    adjustHeights(tmp->left);
                    return;
                }
            } else {
                // go to right subtree
                if (tmp->right != NULL){
                    //No insertion, keep looking
                    cout <<"Looking right of "<<tmp->word<<endl;
                    tmp = tmp->right;
                } else {
                    //If empty, insert here
                    cout<<"Inserting to right of "<<tmp->word<<endl;
                    tmp->right = new NodeT(s);
                    tmp->right->parent = tmp;
                    adjustHeights(tmp->right);
                    return;
                }
            }
        }
    }
}

/* Two main ways of implementing ajustHeights(), both will call updateHeightAfterInsertion() first.
 1. If this is not an AVL tree, updateHeightAfterInsertion() will just updates the tree, and ajustHeights() halts.
 2. If this is an AVL tree, updateHeightAfterInsertion() will find if there is a stop node existed. A stop node
 is the node with balance 2 or -2, which satisfys a rotation. It will return that node, and call the methods of  rotations accordingly. After rotation, it calls updateHeightAfterRotation to update the heights of nodes of the tree.
 */
void AVLTree::adjustHeights(NodeT *n){ //input is the inserted node
    /* After insertion, the balance of the node along the insertion path becomes 2/-2 is the stop node, or if the stop node is NULL it means the tree does not need to be rebalanced(It's either AVL not necessary for rebalancing or it's not AVL)
     */
    NodeT * stopNode = updateHeightAfterInsertion(n);
    // If this is an AVLTree, check balance factors and rebalance if the stop node is found
    if(AVLflag == true && stopNode!= NULL){
        NodeT * returnedNode = NULL;
        if (getDiff(stopNode) == 2){
            if (getDiff(stopNode->left) == 1){
                //LL, do single right rotation on the node that's doubly left heavy(n's stopNode)
                returnedNode = rotateRight(stopNode);
                updateHeightAfterRotation(returnedNode->parent);
            } else if (getDiff(stopNode->left) == -1) {
                //LR, do two rotations. L(stopNode->left) and R(stopNode)
                returnedNode = rotateLeft(stopNode->left);
                updateHeightAfterRotation(returnedNode->parent);
                returnedNode = rotateRight(stopNode);
                updateHeightAfterRotation(returnedNode->parent);
            }
        } else if (getDiff(stopNode) == -2){
            if (getDiff(stopNode->right) == -1){
                //RR, do single left rotation on the node that's doubly left heavy(n's stopNode)
                returnedNode = rotateLeft(stopNode);
                updateHeightAfterRotation(returnedNode->parent);
            } else if (getDiff(stopNode->right) == 1) {
                //RL, do two rotations. R(stopNode->right) and L(stopNode)
                returnedNode = rotateRight(stopNode->right);
                updateHeightAfterRotation(returnedNode->parent);
                returnedNode = rotateLeft(stopNode);
                //double rotations might just need 1 time of update height, will step into later
                updateHeightAfterRotation(returnedNode->parent);
            }
        }
    }
    
}

/* This method will update the height after the insertion of a node,
 and it will rebalance the tree if it's an AVL tree and if it's necessary
 */
NodeT * AVLTree::updateHeightAfterInsertion(NodeT *n){ //input is the inserted node
    NodeT * tmp = n;
    //First, set the height of the inserted node to 1
    tmp->height++;
    int tmpParentOriginalHeight = tmp->parent->height;
    tmp->parent->height = getMax(tmp->parent) + 1; //possible new height
    if(AVLflag == true){
        // if this is AVL and at any time the node is found unblanced, return the node and do rotation
        if(abs(getDiff(tmp->parent)) == 2){
            return tmp->parent;
        }
    }
    while (tmp->parent->height != tmpParentOriginalHeight){ // if height has been updated
        tmp = tmp->parent;
        if (tmp != root){
            tmpParentOriginalHeight = tmp->parent->height;
            tmp->parent->height = getMax(tmp->parent) + 1;
            if(AVLflag == true){
                // if this is AVL and at any time the node is found unblanced, return the node and do rotation
                if(abs(getDiff(tmp->parent)) == 2){
                    return tmp->parent;
                }
            }
        } else {
            // condition loop reaches root, cannot check upwards any more
            if (AVLflag == true){
                if(abs(getDiff(root)) == 2){
                    return root;
                } else {
                    return NULL; //No rotation need
                }
            } else {
                return NULL; // Not AVL, no rotation
            }
        }
    }
    // When reaches the node whose height isn't changed, jump out of the while loop and return NULL
    return NULL;
}

/* Starting from the new root's parent, update its height if it's necessary */
void AVLTree::updateHeightAfterRotation(NodeT *n){ //*n is the parent of the returned node from rotation
    if (n != NULL){
        n->height = getMax(n) + 1;
        n = n->parent;
        while(n != NULL){
            n->height = getMax(n) + 1;
            n = n->parent;
        }
    } else {
        return; //if the returned node is already the root, it's parent is NULL, then no need to update the height of its parent(since it's NULL)
    }
}


/* Helper function to get the max height of children
 to be used to calculate the parent new height
 */
int AVLTree::getMax(NodeT *n){
    if (n->left == NULL && n->right == NULL){
        return 0;
    } else if (n->left == NULL && n->right != NULL){
        return n->right->height;
    } else if (n->right == NULL && n->left != NULL){
        return n->left->height;
    } else {
        if (n->left->height > n->right->height){
            return n->left->height;
        } else {
            return n->right->height;
        }
    }
}

/* Three kinds of tree travesal, written in recursive way. */
void AVLTree::printIO(NodeT *root){ //Note: need the root of the tree taken in
	if (root == NULL){ //Note: This is not the root of the tree, but a local ptr var
		return;
	} else {
		printIO(root->left);
		cout <<"|"<<root->height<<":"<<root->word<<"|"<<endl;
		printIO(root->right);
	}
}
void AVLTree::printPre(NodeT *root){
	if (root == NULL){
		return;
	} else {
		cout <<"|"<<root->height<<":"<<root->word<<"|"<<endl;
		printPre(root->left);
		printPre(root->right);
	}
}
void AVLTree::printPost(NodeT *root){
	if (root == NULL){
		return;
	} else {
		printPost(root->left);
		printPost(root->right);
		cout <<"|"<<root->height<<":"<<root->word<<"|"<<endl;
	}
}

// Methods for AVL Trees only

/* Get the difference between the heights of left child and right child. */
int AVLTree::getDiff(NodeT *n){
    if (n->left == NULL && n->right == NULL){
        return 0;
    } else if (n->left == NULL && n->right != NULL){
        return (0 - n->right->height);
    } else if (n->left != NULL &&n->right == NULL){
        return (n->left->height - 0);
    } else {
        return (n->left->height - n->right->height);
    }
}

/* Left rotation, return the new root of the rotated subtree. */
NodeT * AVLTree::rotateLeft(NodeT *n){
    NodeT * rotatingNodeRightChild = n->right;
    NodeT * rotatingNodeParent = n->parent;
    bool isLeftChild = false;
    if(rotatingNodeParent != NULL){
        if(rotatingNodeParent->left == n){
            isLeftChild = 1;
        } else {
            isLeftChild = 0;
        }
    }
    // Start rotation
    cout <<endl;
    cout <<"Rotating left around "<<n->word<<endl;
    cout <<"Height of node before: "<<n->word<<":"<<n->height<<endl;
    cout <<"Height of right child before: "<<rotatingNodeRightChild->word<<":"<<rotatingNodeRightChild->height<<endl;
    // Rotating process
    n->right = rotatingNodeRightChild->left;
    if(rotatingNodeRightChild->left == NULL){
        cout <<"resetting "<<n->word<<"'s right to NULL"<<endl;
    } else {
        rotatingNodeRightChild->left->parent = n;
        cout <<"resetting "<<n->word<<"'s right to "<<rotatingNodeRightChild->left->word<<endl;
    }
    rotatingNodeRightChild->left = n;
    n->parent = rotatingNodeRightChild;
    cout <<"resetting "<<rotatingNodeRightChild->word<<"'s left to "<<n->word<<endl;
    // assign the parent of the new root after rotation, to the new root
    rotatingNodeRightChild->parent = rotatingNodeParent;
    // assign the new root to the correct position to its parent
    if (rotatingNodeParent != NULL){
        if (isLeftChild == 1){
            rotatingNodeParent->left = rotatingNodeRightChild;
            //rotatingNodeRightChild->parent = rotatingNodeParent;
        } else if (isLeftChild == 0) {
            rotatingNodeParent->right = rotatingNodeRightChild;
            //rotatingNodeRightChild->parent = rotatingNodeParent;
        }
    }
    // End rotation
    
    // update height
    n->height = getMax(n) + 1;
    rotatingNodeRightChild->height = getMax(rotatingNodeRightChild) + 1;
    
    cout <<"After rotation:"<<endl;
    cout<<"height of "<<n->word<<" is now "<<n->height<<endl;
    cout<<"height of "<<rotatingNodeRightChild->word<<" is now "<<rotatingNodeRightChild->height<<endl;
    
    if (rotatingNodeParent == NULL) {
        //This rotatingNode was root, then it's right child will become the new root
        root = rotatingNodeRightChild;
        root->parent = NULL;
        cout<<rotatingNodeRightChild->word<<" is new root"<<endl;
    }
    
    return rotatingNodeRightChild;
}

/* Right rotation, return the new root of the rotated subtree. */
NodeT * AVLTree::rotateRight(NodeT *n){
    NodeT * rotatingNodeLeftChild = n->left;
    NodeT * rotatingNodeParent = n->parent;
    bool isRightChild = false;
    if(rotatingNodeParent != NULL){
        if(rotatingNodeParent->right == n){
            isRightChild = 1;
        } else {
            isRightChild = 0;
        }
    }
    // Start rotation
    cout <<endl;
    cout <<"Rotating right around "<<n->word<<endl;
    cout <<"Height of node before: "<<n->word<<":"<<n->height<<endl;
    cout <<"Height of left child before: "<<rotatingNodeLeftChild->word<<":"<<rotatingNodeLeftChild->height<<endl;
    // Rotating process
    n->left = rotatingNodeLeftChild->right;
    if(rotatingNodeLeftChild->right == NULL){
        cout <<"resetting "<<n->word<<"'s left to NULL"<<endl;
    } else {
        rotatingNodeLeftChild->right->parent = n;
        cout <<"resetting "<<n->word<<"'s left to "<<rotatingNodeLeftChild->right->word<<endl;
    }
    rotatingNodeLeftChild->right = n;
    n->parent = rotatingNodeLeftChild;
    cout <<"resetting "<<rotatingNodeLeftChild->word<<"'s right to "<<n->word<<endl;
    // assign the parent of the new root after rotation, to the new root
    rotatingNodeLeftChild->parent = rotatingNodeParent;
    // assign the new root to the correct position to its parent
    if (rotatingNodeParent != NULL){
        if (isRightChild == 1){
            rotatingNodeParent->right = rotatingNodeLeftChild;
            //rotatingNodeLeftChild->parent = rotatingNodeParent;
        } else if (isRightChild == 0) {
            rotatingNodeParent->left = rotatingNodeLeftChild;
            //rotatingNodeLeftChild->parent = rotatingNodeParent;
        }
    }
    // End rotation

    n->height = getMax(n) + 1;
    rotatingNodeLeftChild->height = getMax(rotatingNodeLeftChild) + 1;
    
    cout <<"After rotation:"<<endl;
    cout<<"height of "<<n->word<<" is now "<<n->height<<endl;
    cout<<"height of "<<rotatingNodeLeftChild->word<<" is now "<<rotatingNodeLeftChild->height<<endl;
    
    if (rotatingNodeParent == NULL) {
        //This rotatingNode was root, then it's left child will become the new root
        root = rotatingNodeLeftChild;
        root->parent = NULL;
        cout<<rotatingNodeLeftChild->word<<" is new root"<<endl;
    }
    
    return rotatingNodeLeftChild;
}
