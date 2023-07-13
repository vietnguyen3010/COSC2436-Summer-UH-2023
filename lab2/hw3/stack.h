#ifndef stack_h
#define stack_h
#include <iostream>
// using namespace std;

template <class T> struct node
{
    T data;
    node *next;
};

template <class T> class stack{
    private: 
        node <T> *top;
        int size;

    public:

        stack(){top = nullptr; size = 0;}
        bool Empty(){
            return (size == 0);
        }
        //deconstructor
        ~stack(){ 
            node <T> *tmp = top;
            while (top != nullptr){
            tmp = top;
            top = top->next;
            delete tmp;

            }
            size = 0;
        }

        T peek(){
            return top->data;
        }

        int getsize(){
            return size;
        }

        void push (T in){
            node <T> *tmp = new node <T>;

            tmp->data = in;
            tmp ->next = nullptr;

            if (top == nullptr)
                top = tmp;

            else {
                tmp ->next = top;
                top = tmp;
            }

            size++;
        }

        void pop(){

            if (top == nullptr)
                return;

            node <T> *tmp = top;
            top = top->next;
            delete tmp;
            size--;
        }

    void print(){
        node <T> *cu = top;
        while (cu != nullptr){
            cout << cu->data <<endl;
            cu = cu->next;
        }
    }

    void reverse() {
        if (top == nullptr || top->next == nullptr)
            return;

        node<T>* prev = nullptr;
        node<T>* current = top;
        node<T>* n = nullptr;

        while (current != nullptr) {
            n = current->next;
            current->next = prev;
            prev = current;
            current = n;
        }

        top = prev;
    }
        
};



#endif