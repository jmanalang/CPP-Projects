#include <stdlib.h>
#include <algorithm>
#include <map>
#include "Lexer.h"
#include "cmd.h"
#include "term_control.h"
#include "error_handling.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib> 

using namespace std;

void prompt() {
    cout << term_cc(BLUE) << "> " << term_cc() << flush;
}

string fname; 

int main(int argc, char **argv) {
	if (argc != 1) error_quit("Usage: main");

	const char *usage_msg = 
		"Commands: \n"
		"	loaddb <filename>\n"
		"	slowintersect\n"
		"	slowintersect <filename>\n"
		"	fastintersect\n"
		"	fastintersect <filename>\n"
		"	slowunion\n"
		"	slowunion <filename>\n"
		"	fastunion\n"
		"	fast union <filename>\n"
		"	exit/quit,bye";
		
		
	map<string, cmd_handler_t> commands;
	commands["loaddb"] = &loaddb;
	commands["slowintersect"] = &slowin;
	commands["slowintersect"] = &slowout;
	commands["fastintersect"] = &fastin;
	commands["fastintersect"] = &fastout;
	commands["slowunion"] = &slowun;
	commands["slowunion"] = &slowun1;
	commands["fastunion"] = &fastun;
	commands["fastunion"] = &fastun1;
	commands["quit"] = &bye;
	commands["exit"] = &bye;
	commands["bye"] = &bye;

	string line; Token tok; Lexer lexer;

	while (cin) {
		prompt();
		getline(cin, line); lexer.set_input(line);
		if (!lexer.has_more_token()) continue;
		tok = lexer.next_token();
		if (tok.type == IDENT) {
			if (commands.find(tok.value) != commands.end()) {
				commands[tok.value](lexer);
				continue;
			}
		}
		note(usage_msg);
	}

	return 0;
}
