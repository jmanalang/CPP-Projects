// ============================================================================ 
// listmanip.cpp
// ~~~~~~~~~~~~~
// JULES MANANLANG
// implement the missing functions
// ============================================================================ 

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include "listmanip.h"
#include "Lexer.h"
#include <list>
#include <cmath>
#include "term_control.h"

using namespace std; // BAD PRACTICE

extern const string usage_msg = "List Manipulation Toy. Version 0.1\n"
                                "Author: Jules Manalang\n"
                                "Report bugs to julesman@buffalo.edu";
/**
 * -----------------------------------------------------------------------------
 * create a new singly linked list containing keys which are integers from 
 * a given vector of tokens
 * return the pointer to the head of the newly created list
 * -----------------------------------------------------------------------------
 */
Node* new_list(const vector<Token>& tok_vec)
{
	string string1;
	int value;
	istringstream (string1) >> value;
	Node* head = NULL;
	if (tok_vec.size() > 1){
		for (int p =  tok_vec.size() - 1; p >= 0; p--){
		string1.clear();
		string1 = tok_vec[p].value;
		istringstream (string1) >> value;
		head = new Node(value, head);
		}	
	}
	return head; // and don't return NULL unless you have to
}

/**
 * -----------------------------------------------------------------------------
 * given the pointers to the heads of two singly linked lists
 * modify (only the pointers of) the first list so that only the common elements
 * remain. 
 * - return the head pointer to the resulting first list
 * - assume the two input list are already sorted and each of them has no
 *   duplicate key. 
 * - if any of of them is not sorted or has duplicate keys, then throw a
 *   runtime_error() with the appropriate message
 * - do remember to free-up the space of the deleted element
 * -----------------------------------------------------------------------------
 */
Node* keep_common(Node* head1, Node* head2)
{
	if (head1 != NULL){
		if(head1->next == NULL){return head1;}
		if(head1->key > head1->next->key){throw runtime_error("First List Not Sorted");}
		if(head1->key == head1->next->key){throw runtime_error("First List Contains Duplicates");}
		if (head2 != NULL){
			if(head2->next == NULL) {return head1;}
			if(head2->key > head2->next->key){throw runtime_error("Second List Not Sorted");}
			if(head2->key == head2->next->key){throw runtime_error("Second List Contains Duplicates");}
			if (head1->key != head2 ->key){
				Node* temp = head1->next;
				head1->next = temp->next;
				delete temp;
				keep_common(head1, head2->next);
			}
		}
	keep_common(head1->next,head2);
	}
	return head1;	
}


/**
 * -----------------------------------------------------------------------------
 * given the pointer to the head of a singly linked list, remove the duplicate
 * elements and return the pointer to the head of the new list
 * return the head pointer to the resulting list
 * - assumes that the given list (pointed to by head) is sorted in
 *   non-decreasing order
 * - if not, throw a runtime_error exception stating the error
 * -----------------------------------------------------------------------------
 */
Node* remove_duplicates(Node* head)
{
	if(head != NULL){
		if(head->next == NULL){return head;}
		if(head->key > head->next->key){throw runtime_error("List Is not Sorted");}
		if(head->key == head->next->key){
			Node* temp = head->next;
			head->next = temp->next;
			delete temp; 
			remove_duplicates(head);
		}
		else{
			remove_duplicates(head->next);
		}
	}
	return head;
}
/**
 * -----------------------------------------------------------------------------
 * merge two sorted lists pointed to by head1 and head2
 * throw runetime_error("Please give me two sorted lists") if any one of them
 * is not already sorted
 * return pointer to the head of the merged list
 * only modify pointers. DONOT modify the key of any node
 * -----------------------------------------------------------------------------
 */
Node* merge_lists(Node* head1, Node* head2) 
{
	if (head2 == NULL){return head1;}
	while(head2 != NULL){
		if(head1->key > head1->next->key){throw runtime_error("Please give me two sorted lists");}
		if(head2->key > head2->next->key){throw runtime_error("Please give me two sorted lists");}
		head1 = new Node(head2->key, head1);
		head2 = head2->next;
	}
	return sort_list(head1);// and don't return NULL unless you have to 
}

/**
 * -----------------------------------------------------------------------------
 * sort the list pointed to by 'head'
 * return the pointer to the head of the new list
 * DO NOT modify the keys, just manipulate the pointers
 * -----------------------------------------------------------------------------
 */
Node* sort_list(Node* head) 
{
	int t = 0;
	Node* current;
	for(bool didSwap = true; didSwap;){
	didSwap = false;
	for(current = head; current->next != NULL; current = current->next){
		if (current->key > current->next->key){
			t = current->key;
			current->key =  current->next->key;
			current->next->key = t;
			didSwap = true;
		}
	}
	}
	return head; // and don't return NULL unless you have to
}

// *****************************************************************************
// DO NOT MODIFY THIS FILE BEYOND THIS POINT
// *****************************************************************************

/**
 * -----------------------------------------------------------------------------
 * free the memory of all nodes starting from ptr down
 * -----------------------------------------------------------------------------
 */
void free_list(Node* ptr) {
	Node* temp;
	while (ptr != NULL) {
		temp = ptr;
		ptr = ptr->next;
		delete temp;
	}
}
