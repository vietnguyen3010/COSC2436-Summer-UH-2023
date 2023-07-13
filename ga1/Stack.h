#include <iostream>
#include <string>
using namespace std;


struct node 
{
    int num;
    node *next;
};

class Stack
{
private:
    node *top;
    int size;
public:
    Stack();
    bool isEmpty();
    void push(int);
    int pop();
    int peek();
    void print();
    int getSize();
};

Stack::Stack()
{
    top = nullptr;
    size = 0;
}

bool Stack::isEmpty()
{
    return top == nullptr;
}

void Stack::push(int n)
{
    node *temp = new node;
    temp->num = n;
    temp->next = nullptr;

    temp->next = top;
    top = temp;
    size++;
}

int Stack::pop()
{
    if (isEmpty())
        return -1;
    else
    {
        node *temp = top;
        int n = temp->num;
        top = temp->next;
        delete temp;
        size--;
        return n;
    }
}

int Stack::peek()
{
    if (isEmpty())
        return -1;
    else
    {
        return top->num;
    }
}

void Stack::print()
{
    node *cu = top;
    while (cu != nullptr)
    {
        cout << cu->num << endl;
        // output << cu->num << endl;
    }
}