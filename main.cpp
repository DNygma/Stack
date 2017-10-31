//Richard Anderson
//Cosc 2340 - 1374135
//Toti

#include <iostream>
#include <string>
#include <fstream>

#include "stack.h"
#include "ArgumentManager.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "Usage: reverse \"A=<file>;C=<file>\"" << std::endl;
		return -1;
	}

	ArgumentManager am(argc, argv);
	string infile = am.get("A");
	string outfile = am.get("C");

	ifstream readfile;
	ofstream outputfile;

	readfile.open(infile.c_str(), ios::in);						// Read in File
	outputfile.open(outfile.c_str(), ios::out);
	string str, word;

	stack<string> towerOfPizza;									//Stack object

	while (!readfile.eof()) {									//Read in file
		getline(readfile, str);							//Remove periods
		stringstream ss(str);
		while (ss >> word)										//Take in one word at a time and push to top of stack
			if (!towerOfPizza.isItFull()) {
				towerOfPizza.PUSHIT(word);
			}

			else {
				towerOfPizza.StacksOnStacks();					//Double the stack when Overflow takes place
				towerOfPizza.PUSHIT(word);
			}
	}

	towerOfPizza.reverseOrder(towerOfPizza, outputfile);		//Print tower in reverse order to outfile

	readfile.close();
	outputfile.close();
	system("pause");
	return 0;
}