#include <iostream>
#include <fstream>
#include "ArgumentManager.h"
using namespace std;

template<typename T>
struct node {
    T data; 
    node *next; 
};

template<typename T>
class ll {
private:
    node<T> *head; 
    int s; 
public:

    ll();
    void addatbegin(T data);
    void addatend(T data);
    void addatindex(T data, int index);
    void remove(T data);
    int getSize() {return s;}
    void print(); 
};

template <typename T>
ll<T>::ll() {
    head = nullptr;
    s = 0;
}

template <typename T>
void ll<T>::addatbegin(T data) {
        // 1. Create a new node
        node<T> *temp = new node<T>;
        temp->data = data;
        temp->next = nullptr;

        if (head == nullptr) { // if the linked list is empty
            head = temp;
        } else {
            temp->next = head; // linked temp node to head 
            head = temp; // Update head 
        }
        s++; // update the size
    }

template <typename T>
void ll<T>::addatend(T data) {
    // 1. Create a new node
    node<T> *temp = new node<T>;
    temp->data = data;
    temp->next = nullptr;

    if (head == nullptr) { // if the linked list is empty
        head = temp;
    } else {
        node<T> *cu = head;

        while (cu->next != nullptr) { // traverse cu pointer to the last node
            cu = cu->next;
        }
        cu->next = temp; // link the last node with temp node 
    }
    s++; // Update size
}

template <typename T>
void ll<T>::addatindex(T data, int index) {
    if (index < 0 || index > getSize()) { 
        return; 
    }
    if (index == 0) { 
        addatbegin(data);
    } else if (index == getSize()) { 
        addatend(data);
    } else {
            
        node<T> *temp = new node<T>;
        temp->data = data;
        temp->next = nullptr;
        node<T> *cu = head;
        // --index;
        // while (index != 1)
        // {
        //     cu = cu->next;
        //     --index;
        // }
        // temp->next = cu->next;
        // cu->next = temp;
          
        for (int i = 0; i < index - 1; i++) {
            cu = cu->next;
        }
           
        temp->next = cu->next;
        cu->next = temp;
        s++;
    }
}

template <typename T>
void ll<T>::remove(T data) {
    if (head == nullptr) { // if linked list is empty
        return; 
    }
    if (head != nullptr) {
        node<T> *cu = head;
        // if the node delete is the first node
        if (head->data == data) {
            head = head->next;
            delete cu;
            s--;
        }
        // the node delete is not the first node either in the linked list
        else {
            node<T> *pre = nullptr;
            while (cu != nullptr && cu->data != data) {
                pre = cu;
                cu = cu->next;
            }
            if (cu != nullptr) {
                pre->next = cu->next;
                delete cu;
                s--;
            }
        }
    }
}

template <typename T>
void ll<T>::print() {
        node<T> *cu = head;
        while (cu != nullptr) {
            cout << cu->data << " ";
            //output << cu->data << " ";
            cu = cu->next;
        }
        //cout << endl;
        //output << endl;
        
    }

string getDatatype(const string &s) {
    return s.substr(0, s.find(' '));
}

int getIndex(const string &s) {
    string index = s.substr(s.find('(') + 1, s.find(')') - s.find('(') - 1);
    return stoi(index);
}

string getData(const string &s) {
    return s.substr(s.find('[') + 1, s.find(']') - s.find('[') - 1);
}

int main(int argc, char *argv[]) {
    ArgumentManager am(argc, argv);
    // ifstream input(am.get("input"));
    // ofstream output(am.get("output"));

    ifstream input("input2.txt");
    ofstream output("output2.txt");

    string dataType, line;

    getline(input, dataType);
    if (input.peek() == EOF)
    {
        input.close();
        output.close();
    }

    if (dataType == "string") {
        ll<string> str;
        while (getline(input, line)) {
     
            if (!line.empty()) {
            
                string t = getDatatype(line);
          
                string data = getData(line);
        
                int idx = -1;
                if (t == "Add") {
                    idx = getIndex(line);
                }

              
                if (t == "Add") {
                    str.addatindex(data, idx);
                } else if (t == "Remove") {
                    str.remove(data);
                }
            }
        }

     
        str.print();
    } else if (dataType == "int") { 
  
        ll<int> in;


        while (getline(input, line)) {
          
            if (!line.empty()) {
                
                string t = getDatatype(line);
    
                int data = stoi(getData(line));

                int idx = -1;
                if (t == "Add") {
                    idx = getIndex(line);
                }

   
                if (t == "Add") {
                    in.addatindex(data, idx);
                } else if (t == "Remove") {
                    in.remove(data);
                }
            }
        }

   
        in.print();
    } else if (dataType == "char") { 
        
        ll<char> c;

      
        while (getline(input, line)) {
         
            if (!line.empty()) {
             
                string t = getDatatype(line);
   
                char data = getData(line)[0];
            
                int idx = -1;
                if (t == "Add") {
                    idx = getIndex(line);
                }

      
                if (t == "Add") {
                    c.addatindex(data, idx);
                } else if (t == "Remove") {
                    c.remove(data);
                }
            }
        }

        c.print();
    }

   
    input.close();

    return 0;
}