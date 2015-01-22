// =============================================================================
// print.cpp
// ~~~~~~~~~
// Jules Manalang		
// - implement the three tree printing routines
// *****************************************************************************
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <map>
#include <vector>
#include <stdexcept>
#include <deque>
#include "BTree.h"
#include "term_control.h"
using namespace std;

// feel free to change the following notice
string version = 
    "UB Tree Program. Version 0.1\n"
    " Author: Jules Manalanng\n"
    " Report bugs to julesman@buffalo.edu\n";

/**
 * -----------------------------------------------------------------------------
 * print a given tree vertically
* -----------------------------------------------------------------------------
 */
void vertical_print(BTNode<string>* root) { 
	if (root != NULL) {
		deque<BTNode<string> > node1;
		node1.push_front(root);
		while(!node1.empty()){	
			if (!node1->right.empty()){
				cout << node1-> payload; 
				cout << '|' <<'_';
			}
			if(!node1->left.empty()){
				cout << '|';
				vertical_print(root->right);
			}
			}




			
	/*		BTNode<string>* cur = node1.back();
			node1.pop_back();
			if(cur->left != NULL) {node1.push_front(cur->left);}
			if(cur->right!= NULL) {node1.push_front(cur->right);}
			cout << cur->payload <<'\n';*/
		}
	
}

/**
 * -----------------------------------------------------------------------------
 * print a given tree horizontally
 * -----------------------------------------------------------------------------
 */
void horizontal_print(BTNode<string>* root) {
	     
}

/**
 * -----------------------------------------------------------------------------
 * print a given tree symmetrically
 * -----------------------------------------------------------------------------
 */
void symmetric_print(BTNode<string>* root) {

}

