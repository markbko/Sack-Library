#include "stack.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using namespace cop4530;

int precedence(string str);
bool alphaTest(string str);
void infix2postfix(vector<string> &infix, vector<string> &outputVector);
void evaluate(vector<string> &outputVector);	
void print(vector<string> &outputVector);

int main(){
	vector<string> inputVector;
	vector<string> outputVector;
	string input;
	
	do{
		cout << "Enter infix expression (\"exit\" to quit): ";
		getline(cin, input);
		outputVector.clear();
		inputVector.clear();
		
		stringstream sstream(input);
		while (sstream >> input)
			inputVector.push_back(input);
		
		cout << "Postfix expression: ";	
		infix2postfix(inputVector, outputVector);
		
		cout << "Postfix evaluation: ";
		evaluate(outputVector);

	}while(input != "exit");
	

	return 0;
}

int precedence(string str){
	if(str == "("|| str == ")")
		return (3);
	else if(str == "*" || str == "/")
		return (2);
	else if(str == "+" || str == "-")
		return (1);
	else
		return 0;
}

void print(vector<string> &outputVector){ 
	for(int i = 0; i < int(outputVector.size()); i++)
			cout << outputVector[i] << " ";
}

bool alphaTest(string str){
	for(int i = 0; i < int(str.size()); i++)
		if(isalnum(str[i]) == false)
			return false;
	return true;
}

void infix2postfix(vector<string> &infix, vector<string> &outputVector){
	Stack<string> tokens;

	for(int i = 0; i < int(infix.size()); ++i){
		if(precedence(infix[i]) != 0){
			if(((tokens.empty() == false) && (tokens.top() != "(")) && (precedence(tokens.top()) >= precedence(infix[i]))){
				while (((tokens.empty() == false) && (tokens.top() != "(")) && (precedence(tokens.top()) >= precedence(infix[i]))){
					outputVector.push_back(tokens.top());
					cout << tokens.top() << " ";
					tokens.pop();
				}
			}
			tokens.push(infix[i]);
			if(infix[i] == ")"){
				tokens.pop();
				while(tokens.top() != "("){
					cout << tokens.top() << " ";
					outputVector.push_back(tokens.top());
					tokens.pop();
				}
				tokens.pop();
			}
		}
		else if(alphaTest(infix[i]) == true){
			outputVector.push_back(infix[i]);
			cout << infix[i] << " ";
		}
	}
	while(tokens.empty() == false){
		cout << tokens.top() << " ";
		outputVector.push_back(tokens.top());
		tokens.pop();
	}
	cout << endl;
}

void evaluate(vector<string> &outputVector){
	Stack<string> tokens;
	bool isNum = false;
	for(int i = 0; i < int(outputVector.size()); i++){
		if(alphaTest(outputVector[i])){
		for(int i = 0; i < int(outputVector.size()); i++){
			if(alphaTest(outputVector[i]) == true)
				tokens.push(outputVector[i]);
			if(precedence(outputVector[i]) != 0){
				int num;
				float val1 = stoi(tokens.top());
				tokens.pop();
				float val2  = stoi(tokens.top());
				tokens.pop();

			switch (outputVector[i][0])  
            {  
				case '+': num = val2  + val1; break;  
				case '-': num = val2  - val1; break;  
				case '*': num = val2  * val1; break;  
				case '/': num = val2  / val1; break;  
              
            }
			tokens.push(to_string(num));
			}
		}
		print(outputVector);	
		cout << "= " << tokens.top() << endl;
	}
	if(!alphaTest(outputVector[i])){
		print(outputVector);
		cout << "= " << endl;
	}
	}
}