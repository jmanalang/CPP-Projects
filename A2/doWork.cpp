#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
int slow(vector<string> vex1, vector<string> vex2){
	int flag;
	for(int i = 0; i < vex1.size()-1; i++){
		flag = 0; 
		for(int x = 0; x<vex2.size()-1; x++){
			if(vex1[i] == vex2[x]){
				cout << "YES: " << vex1[i] <<endl;
				flag++;
			}
		}
		if(flag < 1){
			cout << "NO: " <<vex1[i] <<endl;
		}	
	}		
return 0;	
}
int fast(vector<string> vex1, vector<string> vex2){
	int flag;
	sort(vex2.begin(), vex2.end());
	for(int i = 0; i<vex1.size()-1; i++){
		flag = 0;
		if(binary_search(vex2.begin(),vex2.end(),vex1[i])){
			cout << "YES: " <<vex1[i] <<endl;
			flag++;
		}
		if (flag < 1){
			cout << "NO: " <<vex1[i] <<endl;
		}
	}
return 0;
}
int main(){
	string id, fn1, fn2, line, fileinput1, fileinput2;
	vector<string> v1, v2;
	cout << '\n' <<'\n' <<'\n' <<  "Please enter a \"slow\" or \"fast\"  command" 
	     << " followed by 2 text files with extensions.You may also type \"exit\" to exit the program" <<'\n' 
	     << "EXAMPLE :  fast file1.txt file2.txt" <<'\n' <<'\n' <<endl ;
	while(getline(cin, line)){
		if(line != "exit"){
			istringstream input(line);
			input >>id >>fn1 >>fn2;
			ifstream file1(fn1.c_str());
			ifstream file2(fn2.c_str());	
			if(! file1.fail() && !file2.fail()){
				if(file1.is_open()){
					while (! file1.eof()) {
						getline(file1, fileinput1);
						v1.push_back(fileinput1);
					}
				file1.close();
				}
				if(file2.is_open()){
					while (! file2.eof()){
						getline(file2, fileinput2);
						v2.push_back(fileinput2);
					}
				file2.close();
				}
			
				if(id == "fast"){
					fast(v1,v2);
					v1.clear();
					v2.clear();
				}
				else if(id == "slow"){
					slow(v1,v2);
					v1.clear();
					v2.clear();
				}
				else if(id != "slow" || id != "fast"){
					cout << "There was an error in  your command. Try again" <<endl;	
				}
			}
			else{ cout << "Failure to Open Files! Try again." <<endl; }
		}
		else if (line == "exit"){exit(EXIT_SUCCESS);}	
	}
return 0;
}	
