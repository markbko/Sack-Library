#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

bool isOpenGroup (const string& op)
// post: return true iff the argument signifies the beginning of a grouped
//       expression
{
    return op == "(";
}

bool isCloseGroup (const string& op)
// post: return true iff the argument signifies the end of a grouped expression
{
    return op == ")";
}

bool isGrouping (const string& op)
// post: return true iff the argument signifies the end or the beginning of a 
//       grouped expression
{
    return op == "(" || op == ")"; 
}    

int orderOfOperation (const string& op)
// post: return the relative importance of operators (higher precedence
//       indicates that an operation should be performed earlier)
{
    if (isGrouping(op))              return 1;
    else if (op == "+" || op == "-") return 2;
    else if (op == "*" || op == "/") return 3;
    else                             return 0;
}

vector<string> infixToPostfix (const string& infix)
// pre: infix is a string containing the space separated infix notation
//     form of an expression
// post: a vector is created containing the elements of the expression in
//     postfix notation
{
    stack<string> operators;
    vector<string> postfix;
    
    istringstream in(infix);
    string token;
    while (in >> token)
    {
        int order = orderOfOperation(token);
        
	// order zero indicates an operand; append it to the output vector
        if (order == 0) 
	{
            postfix.push_back(token);
        }
	// nonzero order indciates an operator; pop all previously read 
	// operators of higher order, then push onto stack
	else
	{
	    // do not pop any operators when beginning parenthetical expression
            if (!isOpenGroup(token))
	    {
                while (operators.size() > 0 && orderOfOperation(operators.top()) >= order)
		{
                    if (!isGrouping(operators.top()))
		    {
                        postfix.push_back(operators.top());
                    }
                    operators.pop();
                }
            }
            operators.push(token);
        }
    }

    // pop remaining operators
    while (operators.size() > 0)
    {
        if (!isGrouping(operators.top()))
	{
            postfix.push_back(operators.top());
        }
        operators.pop();
    }
    
    return postfix;    
}

int evaluate (const vector<string>& postfix, int& index)
// pre: postfix is a vector of strings representing elements of an 
//      expression in postfix notation; index is the index of the last element
//      of postfix being evaluated
// post: returns the mathematical evaluation of the expression
//       *** index is now 0 ***
{
    if (index < 0)
    {
        cerr << "ill-formatted vector/illegal index in evaluate()" << endl;
	return -1;
    }
    else if (orderOfOperation(postfix[index]) == 0)
    {
        return atoi(postfix[index].c_str());
    }
    else
    {
        string op = postfix[index];

	index--;
	int b = evaluate(postfix, index);
	index--;
	int a = evaluate(postfix, index);    

	if (op == "*")      return a * b;
	else if (op == "/") return a / b;
	else if (op == "+") return a + b;
	else if (op == "-") return a - b;
        else
	{
	    cerr << "ill-formatted vector/illegal index in evaluate()" << endl;
	    return 0;
	}
    }
}


ostream& operator<< (ostream& out, const vector<string>& data)
{
    for (unsigned int k = 0; k < data.size(); k++)
    {
        out << data[k] << " ";
    }
    return out;
}


int main (int argc, char* argv[])
{
    cout << "Welcome to Arithmetica 0.1!" << endl
         << "---------------------------" << endl;

    string line;
    while (getline(cin, line))
    {
        cout << line << endl;

        vector<string> infix = infixToPostfix(line);
        cout << infix << endl;

        int index = infix.size() - 1;
        int result = evaluate(infix, index);
        cout << result << endl << endl;
    }

    return 0; 
}