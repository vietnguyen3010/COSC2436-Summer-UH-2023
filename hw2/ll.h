#include <string>
#include <fstream>
#include <iostream>

using namespace std;

struct node {
    string data; 
    node *next; 
};

class ll {
private:
    node *head; 
    int s; 
public:
    ll();
    int getSize() {return s;}
    void addatbegin(string data);
    void addatend(string data);
    void addatindex(string data, int index);
    //void remove(string data);
    void removesegments(string data);
    bool checkdup(string in);

    bool checksegments(string sentence);

    void sortAlphabetically();
    void sortlength();   
    void print(ofstream &output); 
};


ll::ll() {
    head = nullptr;
    s = 0;
}

void ll::addatbegin(string data) {
        // 1. Create a new node
        node *temp = new node;
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

void ll::addatend(string data) {
    // 1. Create a new node
    node *temp = new node;
    temp->data = data;
    temp->next = nullptr;

    if (head == nullptr) { // if the linked list is empty
        head = temp;
    } else {
        node *cu = head;

        while (cu->next != nullptr) { // traverse cu pointer to the last node
            cu = cu->next;
        }
        cu->next = temp; // link the last node with temp node 
    }
    s++; // Update size
}

void ll::addatindex(string data, int index) {

    int s = 0;
    node *returnsize = head;
    while (returnsize != nullptr)
    {
        s++;
        returnsize = returnsize->next;
    }

    if (index < 0 || index > s) { 
        return; 
    }
    if (index == 0) { 
        addatbegin(data);
    } else if (index == s) { 
        addatend(data);
    } else {
            
        node *temp = new node;
        temp->data = data;
        temp->next = nullptr;
        node *cu = head;
     
          
        for (int i = 0; i < index - 1; i++) {
            cu = cu->next;
        }
           
        temp->next = cu->next;
        cu->next = temp;
        s++;
        //cout << s << endl;
    }
}

/*void ll::remove(string data) {
    if (head == nullptr) { // if linked list is empty
        return; 
    }
    if (head != nullptr) {
        node *cu = head;
        // if the node delete is the first node
        if (head->data == data) {
            head = head->next;
            delete cu;
            s--;
        }
        // the node delete is not the first node either in the linked list
        else {
            node *pre = nullptr; // Create a null pointer
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
*/

bool ll::checkdup(string in)
{
    if (head == nullptr)
        return false;
    node *cu = head;
    while (cu != nullptr)
    {
        if (cu->data == in)
            return true;
        cu = cu->next;
    }
    return false;
}

void ll::removesegments(string data)
{
    if (head == nullptr)
        return;
    node *cu = head->next;
    node *pre = nullptr;

    while (cu != nullptr)
    {
        if (cu->data.find(data) != -1)
        {
            if (pre == nullptr)
            {
                head = cu->next;
            }
            else 
            {
                pre->next = cu->next;
            }
            node *temp = cu;
            cu = cu->next;
            delete temp;
        }
        else
        {
            pre = cu;
            cu = cu->next;
        }
    }
}

void ll::sortAlphabetically()
{
    if (head == nullptr || head->next == nullptr)
        return;
    node *sorted = nullptr;
    node *cu = head;

    string temp;
    while (cu != nullptr)
    {
        sorted = cu->next;
        while (sorted != nullptr)
        {
            if (cu->data > sorted->data)
            {
                temp = cu->data;
                cu->data = sorted->data;
                sorted->data = temp;
            }
            sorted = sorted->next;
        }
        cu = cu->next;
    }
}

void ll::sortlength()
{
    if (head == nullptr || head->next == nullptr)
        return;
    
    bool swapped;
    node *cu;
    node *pre = nullptr;
    
    do
    {
        swapped = false;
        cu = head;

        while (cu->next != pre)
        {
            if (cu->data.length() > cu->next->data.length())
            {
                string temp = cu->data;
                cu->data = cu->next->data;
                cu->next->data = temp;
                swapped = true;
            }
            cu = cu->next;
        }
    } while (swapped);
}



int getIndex(string &s) {
    string index = s.substr(s.find('(') + 1, s.find(')') - s.find('(') - 1);
    return stoi(index);
}

string getData(string &s) {
    return s.substr(s.find('[') + 1, s.find(']') - s.find('[') - 1);
}

void ll::print(ofstream &output) {
        node *cu = head;
        while (cu != nullptr) {
            cout << cu->data << endl;
            // output << cu->data << endl;
            cu = cu->next;
        }

        
    }