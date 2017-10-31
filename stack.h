#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

//								   Stack Header			                            	//
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

template<class T>
class stack {
public:
	stack();													//Constructor
	stack(stack<T>& copiedStack);								//Copy constructor
	stack<T>& operator=(stack<T>& stack);						//Overload that thing (AO)
	bool isItEmpty();											//Is the stack empty? true else false
	bool isItFull();											//Is the stack full? true else false
	void StacksOnStacks();										//Double the stack when Overflow takes place
	void PUSHIT(T& word);										//Adds item to stackTOP
	T Extractor(string x);										//Checks string for invalid characters
	T TOP();													//Return TOP if stack is not empty
	void POPTOP();												//POPTOP from stack if there is a non empty stack
	void reverseOrder(stack<T>& stackout, ofstream &out);		//Output string to text file
	~stack();													//Destructor

private:
	int sizeMax = 10;											//Initial maxSize of array index
	string stackTOP;											//String at top of stack
	T *ptr_aRay;												//Pointer to stack of strings
	int counter = 0, stackCount = 0;
};

//									STACK Data Members									//
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

template<class T>
stack<T>::stack() {												//Constructor
	ptr_aRay = new T[sizeMax];									//Set pointer to new Array
}

template<class T>
stack<T>::stack(stack<T>& copiedStack) {						//Copy constructor O(n)
	delete[] ptr_aRay;
}

template<class T>
void stack<T>::StacksOnStacks() {								//Double the stack when Overflow takes place
	T *temp = new T[sizeMax * 2];								//Create temp array to double in size
	for (int i = 0; i < sizeMax; i++) {
		temp[i] = ptr_aRay[i];									//Copy over array to temp
	}
	delete[] ptr_aRay;											//Delete ptr_aRay and set to temp
	ptr_aRay = temp;
	sizeMax *= 2;												//Double sizeMax
	stackCount++;												//Stack counter + 1
	temp = NULL;
}

template<class T>
stack<T>& stack<T>::operator=(stack<T>& copiedStack) {			//Overload that thing!!! (AO) O(n)
	if (this != &copiedStack) {
		copyStack(copiedStack);
	}
	return *this;
}

template<class T>
bool stack<T>::isItEmpty() {									//Is the stack empty? true else false O(1)
	return(counter == 0);
}

template<class T>
bool stack<T>::isItFull() {										//Is the stack full? true else false O(1)
	return(counter == sizeMax);
}

template<class T>
void stack<T>::PUSHIT(T& word) {								//Push word into stack
	if (!isItFull()) {											//Check if full
		Extractor(word);										//Send to Extractor function
		if (stackTOP.empty()) {
			return;
		}
		ptr_aRay[counter] = stackTOP;
		counter++;
	}
}

template<class T>
T stack<T>::Extractor(string x) {								//Checks string for invalid characters
	stackTOP = x;												//Word at the top of the list
	x.clear();

	string symbols = { '"', '(', '{', '}', '[', ']', ':', ';'};
	string bad = { '.', '!', '?', ',', '@', '#','$','%','^','&', 
		'*', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

	if ( stackTOP.front() == '!' || stackTOP.front() == '?' 
		|| stackTOP.front() == '.' || stackTOP.front() == ',') {
		 stackTOP.erase();
		return stackTOP;
	}
	else if (stackTOP.back() == '(') {
		stackTOP.erase();
		return stackTOP;
	}
	else if (stackTOP.back() == '.' || stackTOP.back() == ',' 
		|| stackTOP.back() == '!' || stackTOP.back() == '?' 
		|| stackTOP.back() == ')' || stackTOP.back() == '"' 
		|| stackTOP.back() == ']' || stackTOP.back() == '}') {
		stackTOP.pop_back();
	}
	
	else {
		for (int a = 0; a < stackTOP.length(); a++) {
			for (int b = 0; b < symbols.length(); b++) {
				for (int c = 0; c < bad.length(); c++) {
					
					if (stackTOP[0] == symbols[b]) {
						stackTOP.erase(a, 1);
					}
					else if (stackTOP[a] == symbols[b]) {
						stackTOP.erase();
						return stackTOP;
					}
					else if (stackTOP[a] == bad[c]) {
						stackTOP.erase();
						return stackTOP;
					}
				}
			}
		}
	}

	return stackTOP;
}

template<class T>
T stack<T>::TOP() {												//Return TOP if stack is not empty (1)
	return ptr_aRay[counter - 1];								//return top string and decrementing stack by 1
}

template<class T>
void stack<T>::POPTOP() {										//POPTOP from stack if there is a non empty stack O(1)
	if (!isItEmpty()) {
		counter--;
	}
}

template<class T>
void stack<T>::reverseOrder(stack<T>& stackout, ofstream &out) {//Output string to text file
	while (!stackout.isItEmpty()) {
		out << stackout.TOP() << " ";
		cout << stackout.TOP() << " ";
		stackout.POPTOP();
	}
	out << endl << stackCount << endl;
	cout << endl << stackCount << endl;
}

template<class T>
stack<T>::~stack() {											//Destructor O(1)
	delete[]ptr_aRay;
}

#endif															// STACK_H
