#ifndef dll_h
#define dll_h
#include <string>
#include <iostream>
#include <fstream>
#include "stack.h"

using namespace std;

bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

string post2pre(string postfix)
{
    stack <string> s;    
    string pre = "";
    for (int i = 0; i < postfix.length(); i++)
    {
        if (isOperator(postfix[i]))
        {
            string one = s.peek(); 
            s.pop();    
            string two = s.peek(); 
            s.pop();  
            s.push(postfix[i] + two + one);              
        }
        else 
        {
            s.push(string(1, postfix[i]));  
        }
    }
    while (!s.Empty())
    {
        pre += s.peek();
        s.pop();
    }
    return pre; 
}

string pre2post(string in)
{
    stack <string> s;
    for (int i = in.length(); i >= 0; i--)
    {
        if (isOperator(in[i]))
        {
            string one = s.peek(); 
            s.pop();    
            string two = s.peek(); 
            s.pop();    
            s.push(one + two + in[i]);              
        }
        else 
        {
            s.push(string(1, in[i]));  
        }
    }

    return s.peek();
}

template <class T>
struct nodell{
    T data;
    nodell <T> *next = nullptr;
    nodell <T> *prev = nullptr;
};

template <class T>
class dll{
    private:
        int listsize;
        nodell<T> *head;
        nodell<T> *tail;
    public:
        stack<string> st;

        dll();
        ~dll();
        
        nodell <T> *gethead(){return head;}
        nodell <T> *gettail(){return tail;}
        bool empty(){return (listsize == 0);}

        void add2index(int index, T str);
        void add2end(T);
        void add2beg(T);


        void emptyReserve(string in);
        void convertReserve();
        void flipReserve();
        void printReserveSize(ofstream &out);
        void printReserveTop(ofstream &out);
        void pushReserve(string in);
        void popReserve (string index);
        void removeList(string);
        void convertList (string);

        nodell<T> *findnode(int index)
        {
            nodell<T> *tmp = head;
            int i = 0;

            while (i != index){
                tmp = tmp->next;
                i++;
            }
            return tmp;
        }

        int findindex(T input)
        {
            nodell <T> *cu = head;
            if (head == nullptr)
                return -1;

            int index = 0;
            if (input == cu ->data)
                return 0;

            while (cu ->data != input){
                index++;
                cu = cu->next;
            }
            return index;
        }



        void removenode(nodell<T> *str);
        void removeatend();
        void removeatindex(int index);

        void print(ofstream &out);
        void printbackwards(ofstream &out);
};


template <class T>
dll<T>::dll()
{
    head = nullptr;
    tail = nullptr;
    listsize = 0;
}

template <class T>
dll<T>::~dll()
{
    nodell<T> *tmp = head;
    while (head)
    {
        tmp = head;
        head = head->next;
        delete tmp;
    }
    listsize = 0;
}

template<class T>
void dll<T>::add2beg(T x)
{
    nodell<T> *temp = new nodell<T>;
    temp->data = x;
    temp->next = nullptr;
    temp->prev = nullptr;

    if (head == nullptr)
    {
        head = temp;
        tail = temp;
    }
    else 
    {
        temp->next = head;
        head->prev = temp;
    }
    head = temp;
    listsize++;
}

template<class T>
void dll<T>::add2end(T x)
{
    nodell<T> *temp = new nodell<T>;
    temp->data = x;
    if (tail != nullptr)
    {
        tail->next = temp;
        temp->prev = tail;
    }
    else 
    {
        head = temp;

    }
    tail = temp;
    listsize++;
}

template<class T>
void dll<T>::add2index(int index, T x)
{
    if (index <= 0)
        add2beg(x);
    else if (index >= listsize)
        add2end(x);
    else
    {
        nodell<T> *temp = new nodell<T>;
        temp->data = x;
        temp->next = nullptr;
        temp->prev = nullptr;

        nodell<T> *cu = head;

        int count = 0;
        while (count < index - 1)
        {
            cu = cu->next;
            count++;
        }
        temp->prev = cu;
        temp->next = cu->next;
        if (cu->next != nullptr)
        {
            cu->next->prev = temp;
        }
        cu->next = temp;
        listsize++;
    }
}



template <class T>
void dll<T>::emptyReserve(string str)
{
    int index = stoi(str);
    if (index <= 0)
        index = 0;
    while (!st.Empty())
    {
        add2index(index,st.peek());
        st.pop();
    }        
}

template <class T>
void dll<T>::convertReserve()
{
    string temp = st.peek();
    if (temp.find("postfix") != -1 )
        temp = "prefix:"+ post2pre(temp.substr(temp.find(":") + 1));

    else 
        temp = "postfix:"+ pre2post(temp.substr(temp.find(":") + 1));

    st.pop();
    st.push(temp);
}

template <class T>
void dll<T>::flipReserve()
{
    st.reverse();
}

template <class T>
void dll<T>::printReserveSize(ofstream &out)
{
    cout << "Reserve Size: " << st.getsize() << endl << endl;
    out << "Reserve Size: " << st.getsize() << endl << endl;

}

template <class T>
void dll<T>::printReserveTop(ofstream &out)
{
    cout << "Top of Reserve: ";
    out << "Top of Reserve: ";
    if (st.Empty() == 1)
    {
        cout << "EMPTY" << endl << endl;
        out << "EMPTY" << endl << endl;
    }
    else
    {
        cout << st.peek() << endl << endl;
        out << st.peek() << endl << endl;
    }
                
}

template <class T>
void dll<T>::pushReserve(string str)
{
    if (head == nullptr)
        return;
    nodell<T> *temp = head;
    if (str == "prefix" || str == "postfix")
    {
        while (temp !=nullptr)
        {
            if (temp->data.find(str) != -1)
            {
                st.push(temp->data);
            }
            temp = temp->next;
        }
        removeList(str);
    }
    else if (str == "all")
    {
        while (temp != nullptr)
        {
            st.push(temp ->data);
            temp = temp->next;
        }
        removeList(str);
    }
    else 
    {
        int index = stoi(str);
        temp = findnode(index);
        st.push(temp->data);
        removeList(str);
    }

}

template <class T>
void dll<T>::popReserve (string index)
{
    int str = stoi(index);
    add2index(str, st.peek());
    st.pop();
}

template <class T>
void dll<T>::removeList(string str)
{
    if (head == nullptr)
        return;

    nodell<T> *cu = head;
    if (str != "prefix" && str != "postfix" && str != "all")
    {
        int index = stoi(str);
            
        if (index <= 0)
        {
            index = 0;
        }
        else if(index >= listsize)
        {
            return;
        }
         else
            removeatindex(index);
            return;
    }
    else 
    {
        while (cu != nullptr)
        {
            if (cu->data.find(str) != -1)
            {
                nodell<T> *p = cu->prev;
                nodell<T> *n = cu->next;
                if (p != nullptr)
                    p->next = n;
                else
                    head = n;
                if (n != nullptr)
                    n->prev = p;
                else
                    tail = p;
                delete cu;
                listsize--;

            }
            else if (str == "all")
            {
                nodell<T> *p = cu->prev;
                nodell<T> *n = cu->next;
                if (p != nullptr)
                    p->next = n;
                else
                    head = n;
                if (n != nullptr)
                    n->prev = p;
                else
                    tail = p;
                delete cu;
                listsize--;
            }
            cu = cu->next;
        }
    }
}

template <class T>
void dll<T>::convertList(string str)
{
    if (head == nullptr)
        return;

    if (str == "postfix")
    {
        nodell<T> *cu = head;

        while (cu != nullptr)
        {
            if (cu->data.find("postfix") != -1)
            {
                string x1 = cu->data.substr(cu->data.find(":") + 1);
                string x2 = post2pre(x1);
                cu->data = "prefix:"+ x2;
            }
            cu= cu->next;
        }
    }
    else if (str == "prefix")
    {
        nodell<T> *cu = head;
        while (cu != nullptr)
        {
            if (cu->data.find("prefix") != -1)
            {
                string x1 = cu->data.substr(cu->data.find(":") + 1);
                string x2 = pre2post(x1);
                cu->data = "postfix:" + x2;
            }
            cu= cu->next;
        }
    }

    else if (str == "all")
    {
        nodell<T> *cu = head;
        while (cu != nullptr)
        {
            if (cu->data.find("prefix") != -1)
            {
                string x1 = cu->data.substr(cu->data.find(":") + 1);
                string x2 = pre2post(x1);
                cu->data = "postfix:"+ x2 ;
            }
            else if (cu->data.find("postfix") != -1)
            {
                string x1 = cu->data.substr(cu->data.find(":") +1 );
                string x2 = post2pre(x1);
                cu->data = "prefix:"+ x2;
            }

            cu = cu->next;
        }
    }

    else 
    {
        int i = stoi(str);
        if (i <= 0)
        {
            i = 0;
        }
        if (i < 0 || listsize-1 < i)
             return;

        nodell<T> *cu = findnode(i);
        if (cu->data.find("prefix") != -1)
        {
            string x1 = cu->data.substr(cu->data.find(":") + 1);
            string x2 = pre2post(x1);
            cu->data = "postfix:"+ x2;
        }
        else if (cu->data.find("postfix") != -1)
        {
            string x1 = cu->data.substr(cu->data.find(":") + 1);
            string x2 = post2pre(x1);
            cu->data = "prefix:"+ x2;
        }
    }

}

template <class T>
void dll<T>::removenode(nodell<T> *str)
{
    if (str == tail)
    {
        removeatend();
    }
    nodell<T> *temp = str;
    str = str->next;
    str->prev = temp->prev;
    if (head != temp)
    {
        temp->prev->next = str;
    }
    if (temp == head)
    {
        head = str;
    }
    delete temp;
    listsize--;
}

template <class T>
void dll<T>::removeatend()
{
    nodell<T> *temp = tail;
    if (head == tail)
    {
        head = tail = nullptr;
    }
    else 
    {
        tail = tail->prev;
        tail->next = nullptr;
    }
    delete temp;
    listsize--;
}

template <class T>
void dll<T>::removeatindex(int index)
{
    if (index < 0 || listsize - 1 < index)
    {
        return;
    }
    else if (index == listsize - 1)
    {
        removeatend();
    }
    else 
        removenode(findnode(index));
}

template <class T>
void dll<T>::print(ofstream &out)
{
    if (head == nullptr)
    {
        cout << "List:\nEMPTY\n\n";
        out << "List:\nEMPTY\n\n";
        return;
    }
    cout << "List:" << endl;
    nodell<T> *cu = head;
    while (cu != nullptr) {
        cout << cu->data << endl;
        out << cu->data << endl;
        cu = cu->next;
    }
    cout << endl;
    out << endl;
}

template <class T>
void dll<T>::printbackwards(ofstream &out)
{
    nodell<T> *temp = tail;
    cout <<"Reversed List:"<<endl;
    out <<"Reversed List:"<<endl;
    if (tail == nullptr)
    {
        cout<<"EMPTY"<<endl;
        out<<"EMPTY"<<endl;
    }
    while (temp!=nullptr)
    {
        cout <<temp->data <<endl;
        out <<temp->data <<endl;
        temp = temp->prev;
    }
        cout << endl;
        out << endl;
}



#endif