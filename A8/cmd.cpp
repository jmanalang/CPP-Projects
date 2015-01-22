#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdlib.h>   // for exit()
#include <vector>
#include <string.h>
#include "cmd.h"
#include "term_control.h"
#include "error_handling.h"
#include "Lexer.h"
#include <set> 

using namespace std; // BAD practice
ifstream ifs;
string s;

vector<int> vector2;
vector<vector<int> > vector1;


void loaddb(Lexer lex){
	Token tok1 = lex.next_token();
	string fname = tok1.value;
	ifs.open(fname.c_str());
	if(ifs.fail()){
		cerr <<"ERROR: File does not open: Try Another File" << fname << endl;
		ifs.clear();
	} 
	
	else{
		while(getline(ifs, s)){
			vector2.clear();
			int k;
			istringstream iss(s);
			while(iss >> k){
				vector2.push_back(k);
			}
			
			sort(vector2.begin(), vector2.end());
			vector1.push_back(vector2);
		}
		
		for(size_t n = 0; n < vector1.size(); n++){
			for(size_t q = 0; q < vector1[n].size(); q++){
				cout << vector1[n][q] << ' ';
			}
			cout << endl;
		}
	}
}

void slowin(Lexer lex) {
}
void slowout(Lexer lex) {

}
void fastin(Lexer lex) {
}
void fastout(Lexer lex) {
}

void slowun (Lexer lex) {
}

void slowun1 (Lexer lex) {
}

void fastun (Lexer lexer) {
}

void fastun1 (Lexer lexer) {
}

void bye(Lexer l) {
	if (l.has_more_token()) {
		error_return("Usage: exit");
		return;
	}
	exit(0);
}

