// =============================================================================
// AVLTree.cpp
// ~~~~~~~~~~~
// Jules Manalang
// implement the remove function of the AVL tree
// =============================================================================

#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>
using namespace std; // BAD PRACTICE

const string usage_msg = "AVL Tree Driver. Version 0.2\n"
"Author: Jules Manalang\n"                       
"Report bugs to julesman@buffalo.edu";

/**
 * -----------------------------------------------------------------------------
 * Assignment 9: 
 * - implement this function
 * - to remove a node that has one child: splice it out
 * - if it has two children, put its predecessor in its place then splice
 *   the predecessor. This is not the same strategy as in the lecture slides
 *   which uses the successor. The reason is that you can run the applet
 *   at http://webdiis.unizar.es/asignaturas/EDA/AVLTree/avltree.html
 *   to verify whether your implementation is correct, and that applet uses
 *   the predecessor strategy.
 * - adjust the balance fields correctly, fix balances and rotate
 *   up to the root
 * - all the rotate functions have already been implemented
 * - I STRONGLY suggest that you read and understand the insert function that I
 *   implemented in the file AVLTree.cpp
 * - you can add (private) methods to AVLTree class in AVLTree.h to help out
 * - so the two files your can modify are AVLremove.cpp and AVLTree.h
 *
 * RETURN: 
 * - true if a key was removed
 * - false if the key does not exist
 * -----------------------------------------------------------------------------
 */
template <typename Key>
bool AVLTree<Key>::remove(Key key) {
	AVLNode* node0 = NULL;
	AVLNode* node1 = search(root_, key);
	bool left_node0;
	bool flag = false;
	if(node1==NULL){
		return false;
	}

	if(node1->left==NULL || node1->right == NULL){
		if (node1->left ==NULL){
			node0 = node1->right;
		}
		else{
			node0 = node1->left;
		}
	}
	
	else{
		node0 = node1->right;

		while(node0->left != NULL){
			node0 = node0->left;
		}
		
		node1->key = node0->key;
		node1 = node0;
		node0 = node0->right;
	}
	
	AVLNode* parent1 = node1->parent;
	if(parent1 == NULL){
		root_ = node0;
	}
	else {
		if(node1 == parent1->left){
			parent1->left = node0;
			left_node0 = true;
		}
		else {
			parent1->right = node0;
			left_node0 = false;
		}
	}
	delete node1;




	if (node0 != NULL){
		node0->parent = parent1;
	}
	if (parent1 == NULL){
		return true;
	}


	while (flag==false && parent1 !=NULL){
			if(left_node0){
				switch(parent1->balance){
					case AVLNode::RIGHT_HEAVY:
						node1 = parent1->right;
						switch(node1->balance){
							case AVLNode::RIGHT_HEAVY:
								parent1->balance = AVLNode::BALANCED;
								node1->balance = AVLNode::BALANCED;
								left_rotate(parent1);
							break;
						
							case AVLNode::LEFT_HEAVY:
								node1->left->balance = AVLNode::BALANCED;
								if (node1->left->balance >= 0){
									parent1->balance = 0;
									node1->balance = 0;
								}
								else {
									parent1->balance = 1;
									node1->balance = -1;
								}
								left_rotate(parent1);
								right_rotate(node1);
							break;
					
							case AVLNode::BALANCED:
								node1->balance = AVLNode::RIGHT_HEAVY;
								parent1->balance = AVLNode::LEFT_HEAVY;
								right_rotate(parent1);
								flag = true;
							break;
						}
					break;

					case AVLNode::LEFT_HEAVY:	
						parent1->balance=AVLNode::BALANCED;
					break;

					case AVLNode::BALANCED:
						parent1->balance=AVLNode::RIGHT_HEAVY;
						flag = true;
					break;
		
				}
			}
			else{
				switch(parent1->balance){
					case AVLNode::LEFT_HEAVY:
						node1 = parent1->right;
						switch(node1->balance){
							case AVLNode::LEFT_HEAVY:
								parent1->balance = AVLNode::BALANCED;
								node1->balance = AVLNode::BALANCED;
								right_rotate(parent1);
							break;
						
							case AVLNode::RIGHT_HEAVY:
								node1->left->balance = AVLNode::BALANCED;
								if (node1->left->balance >= 0){
									parent1->balance = 0;
									node1->balance = 0;
								}
								else {
									parent1->balance = 1;
									node1->balance = -1;
								}

								right_rotate(parent1);
								left_rotate(node1);
							break;
					
							case AVLNode::BALANCED:
								parent1->balance = AVLNode::RIGHT_HEAVY;
								node1->balance = AVLNode::LEFT_HEAVY;
								right_rotate(parent1);
								flag = true;
							break;
						}
					break;

					case AVLNode::RIGHT_HEAVY:
						parent1->balance=AVLNode::BALANCED;
					break;

					case AVLNode::BALANCED:
						parent1->balance=AVLNode::LEFT_HEAVY;
						flag = true;
					break;
			
				}
			}
			node0 = parent1;
			parent1 = parent1->parent;
			if(parent1 !=NULL){
				if(node0 == parent1->left){
					left_node0 = true;
				}
				else left_node0=false;
			}
		}		
	return true;
}

