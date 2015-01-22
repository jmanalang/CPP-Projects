// =============================================================================
// main.cpp
// ~~~~~~~~
// Hung Q. Ngo
// - read a tree, print in nice formats
// =============================================================================
#include <iostream>
#include <string>
#include <iterator>
#include <map>
#include <stdexcept>
#include <algorithm> // for sort()
#include <sstream>
#include <vector>
#include <cstdlib>   // for exit()

#include "BTree.h"
#include "term_control.h"
#include "error_handling.h"
using namespace std;

// -----------------------------------------------------------------------------
// prototypes of 3 functions you're supposed to write
// -----------------------------------------------------------------------------
void vertical_print(BTNode<string>* tree);
void horizontal_print(BTNode<string>* tree);
void symmetric_print(BTNode<string>* tree);
extern string version; // defined in print.cpp

// -----------------------------------------------------------------------------
// prototypes of some other functions used in this driver
// -----------------------------------------------------------------------------
void prompt() { cout << term_cc(BLUE) << "> " << term_cc() << flush; }

typedef void (*cmd_t)();

void new_tree();   // returns a new tree or throw an exception if syntax error
void preorder();   // print the current tree in preorder
void postorder();  // print the current tree in postorder
void inorder();    // print the current tree in inorder
void levelorder(); // print the current tree in levelorder
void vertical();   // print the current tree vertically
void horizontal(); // print the current tree horizontally
void symmetric();  // print the current tree symmetrically
void bye();        // simply quit

BTNode<string>* tree = NULL; // new_tree changes this variable

/**
 * -----------------------------------------------------------------------------
 * main body: I avoided the use of Lexer to simplify the code as Lexing is 
 * overkill for this assignment
 * -----------------------------------------------------------------------------
 */
int main() 
{
    map<string,cmd_t> cmd_map;
    cmd_map["newtree"]    = &new_tree;
    cmd_map["exit"]       = &bye;
    cmd_map["bye"]        = &bye;
    cmd_map["preorder"]   = &preorder;
    cmd_map["postorder"]  = &postorder;
    cmd_map["levelorder"] = &levelorder;
    cmd_map["inorder"]    = &inorder;
    cmd_map["ver"]        = &vertical;
    cmd_map["hor"]        = &horizontal;
    cmd_map["sym"]        = &symmetric;

    cout << term_cc(YELLOW) << version;

    string cmd;
    while (cin) {
        prompt(); getline(cin, cmd);
        if (cmd_map.find(cmd) != cmd_map.end()) {
            try {
                cmd_map[cmd]();
            } catch (runtime_error &e) {
                error_return(e.what());
            }
        } else {
            error_return("Unknown command");
        }
    }
    clear_tree(tree);
    return 0;
}

/**
 * -----------------------------------------------------------------------------
 * quick tokenization
 * -----------------------------------------------------------------------------
 */
vector<string> tokenize_line(string const& line)
{
    istringstream iss(line);
    istream_iterator<string> cur(iss), end;
    return vector<string>(cur, end);
}

/**
 * -----------------------------------------------------------------------------
 * check if one vector is a permutation of the other
 * -----------------------------------------------------------------------------
 */
bool is_permutation(vector<string> a, vector<string> b) 
{
    if (a.size() != b.size()) return false;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    for (size_t i=0; i<a.size(); i++) {
        if (a[i].compare(b[i]) != 0) return false;
    }
    return true;
}

/**
 * -----------------------------------------------------------------------------
 * recursively construct a tree from a preorder vector and an inorder vector
 * a[a_start, ..., a_end] is the preorder vector
 * b[b_start, ..., b_end] is the inorder vector
 * -----------------------------------------------------------------------------
 */
BTNode<string>* get_tree(
        const vector<string>& a, size_t a_start, 
        const vector<string>& b, size_t b_start, size_t len)
{
    if (len == 0) return NULL;

    BTNode<string>* node = new BTNode<string>(a[a_start]);

    size_t i;
    for (i=0; i<len; i++) {
        if (b[b_start+i].compare(a[a_start]) == 0) break;
    }
    if (i == len) 
        throw runtime_error("Invalid pair of in/pre-order sequences");

    node->left  = get_tree(a, a_start+1, b, b_start, i);
    node->right = get_tree(a, a_start+i+1, b, b_start+i+1, len-i-1);
    return node;
}

/*
 * -----------------------------------------------------------------------------
 * construct a new tree by reading two lines - a preorder line and an 
 * inorder line
 * -----------------------------------------------------------------------------
 */
void new_tree() 
{
    string poline; // preorder line
    string ioline; // inorder line

    cout << term_cc(YELLOW) 
        << "Enter the preorder and inorder sequences for"
        << " your tree, use unique names\n";

    cout << term_cc(CYAN) << "Preor. seq.: " << term_cc();
    getline(cin, poline);
    cout << term_cc(CYAN) << "Inor. seq. : " << term_cc();
    getline(cin, ioline);
    vector<string> povec = tokenize_line(poline);
    vector<string> iovec = tokenize_line(ioline);

    // ok, now check if one is a permutation of the other
    if (!is_permutation(povec, iovec)) {
        throw runtime_error("Invalid pre/inorder sequence pair");
    }
    clear_tree(tree);
    tree = get_tree(povec, 0, iovec, 0, iovec.size());
}

/**
 * -----------------------------------------------------------------------------
 * print the current tree in preorder
 * -----------------------------------------------------------------------------
 */
void preorder() {
    cout << term_cc(CYAN); 
    preorder_print(tree); 
    cout << endl << term_cc();
}

/**
 * -----------------------------------------------------------------------------
 * print the current tree in levelorder
 * -----------------------------------------------------------------------------
 */
void levelorder() {
    cout << term_cc(CYAN); 
    levelorder_print(tree);
    cout << endl << term_cc();
}

/**
 * -----------------------------------------------------------------------------
 * print the current tree in post order
 * -----------------------------------------------------------------------------
 */
void postorder() 
{
    cout << term_cc(CYAN); 
    postorder_print(tree);
    cout << endl << term_cc();
}

/**
 * -----------------------------------------------------------------------------
 * print the current tree in inorder 
 * -----------------------------------------------------------------------------
 */
void inorder() 
{
    cout << term_cc(CYAN); 
    inorder_print(tree);
    cout << endl << term_cc();
}

/**
 * -----------------------------------------------------------------------------
 * print the current tree symmetrically
 * -----------------------------------------------------------------------------
 */
void symmetric() 
{
    cout << term_cc(CYAN); 
    symmetric_print(tree);
    cout << endl << term_cc();
}

/*
 * -----------------------------------------------------------------------------
 * print the current tree vertically
 * -----------------------------------------------------------------------------
 */
void vertical() 
{
    cout << term_cc(CYAN); 
    vertical_print(tree);
    cout << endl << term_cc();
}

/**
 * -----------------------------------------------------------------------------
 * print the current tree horizontally
 * -----------------------------------------------------------------------------
 */
void horizontal() 
{
    cout << term_cc(CYAN); 
    horizontal_print(tree);
    cout << endl << term_cc();
}

/**
 * -----------------------------------------------------------------------------
 * just quit
 * -----------------------------------------------------------------------------
 */
void bye() 
{
    exit(0);
}

