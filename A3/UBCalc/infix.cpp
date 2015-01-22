// ============================================================================ 
// infix.cpp
// ~~~~~~~~~
// Jules Manalang
// - implement two functions, one to verify whether an infix expression is valid
//   and the other one evaluate the given infix expression
// ============================================================================ 
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <stack>

#include "Lexer.h"
#include "Postfix_Evaluator.h"
#include "error_handling.h"
#include "infix.h"

using namespace std; // BAD practice

extern const string usage_msg = "UB Calculator Program. Version 0.1\n"
"  Author: Jules Manalang\n"
"  Report bugs to julesman@buffalo.edu\n"
"  Or Don't. Please Don't email me" ;
bool compare(Token t1, Token t2){
	string s1 = t1.value; 
	string s2 = t2.value;
	map<string, char> order;
	order["}"] = 'a';
	order[")"] = 'a';
	order["]"] = 'a';
	order["{"] = 'a';
	order["("] = 'a';
	order["["] = 'a';
	order["="] = 'a';
	order["+"] = 'b';
	order["-"] = 'b'; 
	order["*"] = 'c';
	order["/"] = 'c';
	return (order[s1] <= order[s2]);
}
bool compareValues(Token v1, Token v2) {
	string s3 = v1.value;
	string s4 = v2.value;
	map<string, int> bracks ;
	bracks["("] = 3;
	bracks["["] = 2;
	bracks["{"] = 1;
	bracks[")"] = 3;
	bracks["]"] = 2;
	bracks["}"] = 1;
	return (bracks[s3] == bracks[s4]);
}
vector<Token> shuntingYardAlg(vector<Token> vec) {
	stack<Token> store;
	vector<Token> dumpVector;
	for(size_t i = 0; i < vec.size(); i++){
		Token v = vec[i];   
		switch(v.type){
			case NUMBER:
				dumpVector.push_back(v);  
				break; 
			case OPERATOR:               
				if(store.size() == 0){
					store.push(v);    
				} 
				else{
					if(compare(v, store.top())){           
						dumpVector.push_back(store.top());
						store.pop();
						store.push(v);
					}
					else{
						store.push(v);
					}
				}
				break;
			case DELIM:   
				if(v.value == "(" || v.value == "[" || v.value == "{"){
					store.push(v);
				} 
				else{
					while ((store.top()).value != "(" && (store.top()).value != "[" && (store.top()).value != "{") {
						dumpVector.push_back(store.top());
						store.pop();
					}			
					if(compareValues(v, store.top())) {
						store.pop();
					}   
				}
				break;

			case IDENT:
				break;

			case STRING:
				break;

			case ENDTOK:
				break;

			case ERRTOK:
				break;

			case COMMENT:
				break;
		}
	}

	while(!store.empty()){
		dumpVector.push_back(store.top());
		store.pop();
	}
	return dumpVector;
}

/**
 * -----------------------------------------------------------------------------
 * return true if the infix expression given by the token vector 'ie' is valid
 * false if it is invalid
 * we don't care whether the variables are defined in the expressions, thus
 * (a+0.4)*bcd - [(4+4.5)/2 - x]/3.0 is valid
 * even if the variables a, bcd, and x are not assigned previously
 * -----------------------------------------------------------------------------
 */
bool validate_infix_expr(vector<Token> ie)
{
	// YOUR CODE GOES HERE
	return false;
}

/**
 * -----------------------------------------------------------------------------
 * convert an infix expression into postfix using the Shunting Yard algo
 * evaluate it and return, using the postfix evaluator
 * - ie is a token list of tokens forming the expression
 * - sym_tab is a symbol table, holding the values of variables already defined
 * - when anything goes not as expected, throw a runtime_error exception
 *   + undefined identifier (i.e. can't find it in sym_tab)
 *   + wrong infix expression (syntax error)
 *   + etc.
 * -----------------------------------------------------------------------------
 */
double eval_infix_expr(vector<Token> ie, map<string,double> sym_tab)
{
	vector<Token> postfix_expr;

	// convert ie in to a postfix expression, stored in postfix_expr

	postfix_expr = shuntingYardAlg(ie);

	// call the postfix evaluator to evaluate it
	Postfix_Evaluator pe(postfix_expr);
	return pe.eval();
}
