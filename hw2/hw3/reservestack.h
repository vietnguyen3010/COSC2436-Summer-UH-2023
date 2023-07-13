#include <iostream>
#include <string>
#include "stack.h"

using namespace std;

struct reserveStackNode
{
    string type;
    string eq;
    reserveStackNode *next;
};


class ReserveStack
{
private:
    reserveStackNode *top;
    int size;

public:
    ReserveStack();
    bool isEmpty() {return top == nullptr;}
    int getSize() {return size;}
    reserveStackNode* peek() {return top;}
    void push(string, string);
    // bool pop();
    void pop();
    void print();
  
    void convert();

    bool isOperator(char c);
    string prefixtopostfix(string prefix);
    string postfixtoprefix(string postfix);
    void operator = (reserveStackNode *);
};

ReserveStack::ReserveStack()
{
    top = nullptr;
    size = 0;
}

void ReserveStack::push(string t, string e)
{
    reserveStackNode *temp = new reserveStackNode;
    temp->type = t;
    temp->eq = e;
    temp->next = nullptr;

    if (isEmpty())
    {
        top = temp;
    }
    else 
    {
        temp->next = top;
        top = temp;
        size++;
    }
}


void ReserveStack::pop()
{
    if (isEmpty())
    {
        return;
    }
    else 
    {
        reserveStackNode* temp = top;
        top = top->next;
        delete temp;
        size--;
    }
}

// bool ReserveStack::pop()
// {
//     if (size >= 1)
//     {
//         reserveStackNode* temp = top;
//         top = top->next;
//         delete temp;
//         size--;
//         return true;
//     }
//     else
//         return false;
// }

bool ReserveStack::isOperator(char c) 
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

string ReserveStack::prefixtopostfix(string prefix)
{
	stack s;
	for (int i = prefix.size() - 1; i >= 0; i++)
	{
		if (isOperator(prefix[i]))
		{
			string one = s.peek();
			s.pop();
			string two = s.peek();
			s.pop();

			string temp = one + two + prefix[i];
			s.push(temp);
		}
		else
		{
			s.push(string(1, prefix[i]));
		}

	}
	return s.peek();
}

string ReserveStack::postfixtoprefix(string postfix)
{
	stack s;
	for (int i = 0; i < postfix.size(); i++)
	{
		if (isOperator(postfix[i]))
		{
			string one = s.peek();
			s.pop();
			string two = s.peek();
			s.pop();

			string temp = postfix[i] + one + two;
			s.push(temp);
		}
		else 
		{
			s.push(string(1, postfix[i]));
		}
	}
	return s.peek();
}

void ReserveStack::convert()
{
    if (top->type == "prefix")
    {
        top->type = "postfix";
        top->eq = prefixtopostfix(top->eq);
    }
    else
    {
        top->type = "prefix";
        top->eq = postfixtoprefix(top->eq);
    }
}

void ReserveStack::operator= (reserveStackNode* t) {
    top = t;
}