#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std; //BAD

string line, pattern, fname, fileName, identifier;
int z;

ifstream ifs; //input
/* The following Morris-Pratt code is based originally from github user andmej
and has been adapted for this assignment.
*/
void MorrisPratt (string w, string p) {
	int x = p.length();
	vector<int> border(x+1);
	border[0] = -1;
	for (int r = 0; r < x; ++r) {
		border[r+1]= border[-1];
		while(border[r+1] > -1 && p[border[r+1]] != p[r]){
		border[r+1] = border[border[r+1]];
		}
	border[r++];
	}
	
	int t = w.length();
	int l = 0;
	for (int d = 0; d < t; ++d) {
		while (l >-1 && p[l] != w[d]) {
			l = border[l];
		}
		if (++l == x) {
			
			cout << d - x+1 << endl;
			l = border[x];
		}
	}
}
	

int BruteForce (string w, string p) {
	int n = w.length();
	int m = p.length();
	for (int i = 0; i <n-m; i++) {
		int k = 0;
		while((k<m) and w[i+k] == p[k]) {
	        	k = k+1;
		}
		if (k == m) {
			cout << i << " " << endl;
		}
			else{
				continue;
				return i;
			}
		}
	return 0;

}

int main() {
	int i;
	int s = 0;
	cout << "Enter a bf or mf command followed by a quoted string and the file name." << '\n' << '\n'  << '\n';
	cout << "EXAMPLE :   bf \"hi\" input.txt" <<'\n' << '\n';
	cout << "Or type \"exit\" to escape the program"  << '\n' << '\n'; 
	cout << "ENTER A COMMAND NOW   :    "; 
	while (getline(cin,fname)) {
		if(fname != "exit"){
		for (z = 0; z <fname.length(); z++) {
			switch(s) {
			case 0:
				if(fname[z] == '"') {
					s = 1;
				}					
					else {
						identifier += fname[z];
					}
				break;
			case 1:
				if(fname[z] == '"' and ' ') {
					z++;
					s = 2;
				}
					else {
						pattern += fname[z];
					}
				break;
			case 2:
				fileName += fname[z];
				ifs.open (fileName.c_str());
				
				break;
			default: 
				break;
			} 
		
		}
	}	
		else if(fname == "exit") { exit(EXIT_SUCCESS);}
	

	if (identifier == "bf ") {
		i = 0;
			while (getline(ifs, line)) {
				cout << "LINE " << i++  << " : ";
				BruteForce(line, pattern);
				cout << endl;
			}
		
		ifs.close();
		s = 0;
		fname = "";
		fileName = "";
		identifier = "";
		pattern = "";
		
	}

		else if(identifier == "mp ") {			
		i = 0;
			while (getline (ifs, line)) {
				cout << "Line " << i++ << " : ";
				MorrisPratt(line, pattern);
				cout << endl;
				}
			
			ifs.close();
		s = 0;
		fname = "";
		fileName = "";
		identifier =  "";
		pattern  = "";
		}
		else if (identifier != "mp " or identifier != "bf ") {
		cout << "The day your commands work is the day cinnamon buns grow wings and fly.";
		cout <<endl;  
		s = 0;
	        fname = "";
                fileName = "";
                identifier =  "";
                pattern  = "";
		}
	}
	return 0;
}	
	

