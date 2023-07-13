#ifndef stack_h
#define stack_h
#include <iostream>
using namespace std;

template <class T> 
struct stacknode
{
    T data;
    stacknode *next;
};

template <class T>
class stack{
    private: 
        stacknode<T> *top;
        int size;

    public:

        stack();
        ~stack();
        bool Empty(){return (size == 0);};
        T peek() {return top->data;};
        int getsize() {return size;};
        void push(T in);
        void pop();
        void print();
        void reverse();

};


template <class T> 
stack<T>::stack()
{
    top = nullptr;
    size = 0;
}

template <class T> 
stack<T>::~stack()
{
    stacknode <T> *cu = top;
    while (top != nullptr)
    {
        cu = top;
        top = top->next;
        delete cu;

    }
    size = 0;
}

template <class T> 
void stack<T>::push(T d)
{
    stacknode <T> *temp = new stacknode <T>;
    temp->data = d;
    temp->next = nullptr;

    if (top == nullptr)
        top = temp;

    else 
    {
        temp->next = top;
        top = temp;
    }
        size++;
}

template <class T> 
void stack<T>::pop()
{
    if (top == nullptr)
        return;
    else
    {    
        stacknode <T> *cu = top;
        top = top->next;
        delete cu;
        size--;
    } 
}

template <class T> 
void stack<T>::print()
{
    stacknode <T> *cu = top;
    while (cu != nullptr)
    {
        cout << cu->data <<endl;
        cu = cu->next;
    }
}

template <class T> 
void stack<T>::reverse()
{
    if (top == nullptr || top->next == nullptr)
        return;

    stacknode<T>* prev = nullptr;
    stacknode<T>* cu = top;
    stacknode<T>* n = nullptr;

    while (cu != nullptr)
    {
        n = cu->next;
        cu->next = prev;
        prev = cu;
        cu = n;
    }

    top = prev;

};

#endif
