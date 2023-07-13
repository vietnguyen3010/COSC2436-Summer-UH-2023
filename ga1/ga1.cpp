
#include <iostream>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>
#include "ArgumentManager.h"

using namespace std;

class LL{
private:
  struct NodeL{
  int data;
  NodeL *next;
  };
  NodeL *head;
public:

  LL():head(nullptr){}

void reverse() {
    if(head == nullptr || head->next == nullptr) {
        return;
    }
    head = reverse_recursive(nullptr, head);
}

NodeL* reverse_recursive(NodeL* prev_node, NodeL* current_node) {
    NodeL* next_node = current_node->next;
    current_node->next = prev_node;

    if(next_node == nullptr) {
        return current_node;
    }
    return reverse_recursive(current_node, next_node);
}


LL merge_lists(const LL& list1, const LL& list2, LL& combined) {
    merge_lists_recursive(list1.head, list2.head, combined);
    return combined;
}

void merge_lists_recursive(const NodeL* node1, const NodeL* node2, LL& combined) {
  if(node1 != nullptr && node2 != nullptr)
  {
    combined.insert_atpos(node1->data);
    merge_lists_recursive(node1->next, node2, combined);
  }
  else if(node1 == nullptr && node2 != nullptr)
  {
    combined.insert_atpos(node2->data);
    merge_lists_recursive(node1, node2->next, combined);
  }
  else if(node1 == nullptr && node2 == nullptr)
    return;
}

void remove_index(int index) {
    remove_index_recursive(nullptr, head, index);
    
}

void remove_index_recursive(NodeL *prev, NodeL *curr, int index) {
    // If the current node is null, then the index was out of range
    if (curr == nullptr) {
        return;
    }

    // If the index is zero, we're at the node to remove
    if (index == 0) {
        // If there's a previous node, set its next to skip over the current node
        if (prev != nullptr) {
            prev->next = curr->next;
            delete curr; // Delete the node
        } 
        // If there isn't a previous node, we're removing the head, so we have to change the head pointer.
        // This situation is not handled in this function because the head variable is not accessible.
        // You could pass the reference of head as a parameter or redesign your structure to have classes with member functions.

        return;
    }

    // If the index is not zero, move on to the next node
    remove_index_recursive(curr, curr->next, index - 1);
}



void remove_value(int value, bool &name) {
    remove_value_recursive(nullptr, head, value, name);
}

void remove_value_recursive(NodeL* prev_node, NodeL* current_node, int &value, bool &name) {
    if (current_node == nullptr) {
        cout << "Value " << value << " not found in the list." << endl;
        name = false;
        return;
    }

    if (current_node->data == value) {
        if (prev_node == nullptr) { // If the node to delete is the head node
            head = current_node->next;
        } else {
            prev_node->next = current_node->next;
        }
        delete current_node;
        current_node = nullptr;
        cout << "Value " << value << " deleted successfully." << endl;
        name = true;
        return;
    }

    remove_value_recursive(current_node, current_node->next, value, name);
}



void insert_atpos(int value, int pos = 0) {
    head = insert_atpos_recursive(head, value, pos);
}

NodeL* insert_atpos_recursive(NodeL* current_node, int value, int pos) {
    if (pos <= 0 || current_node == nullptr) {
        NodeL* newnode = new NodeL;
        newnode->data = value;
        newnode->next = current_node;
        cout << "Value " << value << " inserted at position " << pos << " successfully." << endl;
        return newnode;
    }

    current_node->next = insert_atpos_recursive(current_node->next, value, pos - 1);
    return current_node;
}

  
  void print_recursive(NodeL* node, ofstream &out) {
      if(node->next == nullptr) {
          out << node->data << "]" << endl;
          return;
      }
      out << node->data << ", ";
      print_recursive(node->next, out);
  }
  
  void print(ofstream &out) {
      if(head == nullptr) {
          out << "List is empty." << endl;
      } else {
          out << "[";
          print_recursive(head, out);
      }
  }
    void print_recursive2(NodeL* node, ofstream &out) {
      if(node->next == nullptr) {
          out << node->data << " |" << endl;
          return;
      }
      out << node->data << " | ";
      print_recursive2(node->next, out);
  }
  
  void print2(ofstream &out) {
      if(head == nullptr) {
          out << "List is empty." << endl;
      } else {
          out << "| ";
          print_recursive2(head, out);
      }
  }
};

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* topNode; // Pointer to the top node of the stack

public:
    Stack() : topNode(nullptr) {}

    bool isEmpty() const {
        return topNode == nullptr;
    }

    void push(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
    }

    T pop() {
        if (isEmpty()) {
            throw runtime_error("Stack is empty. Cannot pop element.");
        }

        T value = topNode->data;
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;

        return value;
    }

    T top() const {
        if (isEmpty()) {
            throw runtime_error("Stack is empty. Cannot retrieve top element.");
        }

        return topNode->data;
    }

    ~Stack() {
        while (topNode != nullptr) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }
};



bool hasCorrectBrackets(string expression, int &counter) {
    Stack<char> brackets;

    for (char c : expression) {
        if (c == '(' || c == '{' || c == '[') {
            brackets.push(c);
        } else if (c == ')' || c == '}' || c == ']') {
            if (brackets.isEmpty()) {
                cout << "Invalid expression" << endl;
                counter++;
                return false;  // Unmatched closing bracket
            }

            char top = brackets.top();
            brackets.pop();

            if ((c == ')' && top != '(') ||
                (c == '}' && top != '{') ||
                (c == ']' && top != '[')) {
                cout << "Invalid expression" << endl;
                counter++;
                return false;  // Mismatched opening and closing brackets
            }
        }
    }

    if(brackets.isEmpty())
      return true;
    else
    {
      counter++;
      cout << "Invalid expression" << endl;
      return false;
    }
}
 
int precedence(char op){
    if(op == '+'||op == '-')
    return 1;
    if(op == '*'||op == '/')
    return 2;
    return 0;
}
 
int applyOp(int a, int b, char op){
    switch(op){
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
}
 
int evaluate(string tokens){
    int i;
    Stack <int> values;
    Stack <char> ops;
    for(i = 0; i < tokens.length(); i++){
        if(tokens[i] == ' ')
            continue;
        else if(tokens[i] == '(' || tokens[i] == '{' || tokens[i] == '['){
            ops.push(tokens[i]);
        }
        else if(isdigit(tokens[i])){
            int val = 0;
            while(i < tokens.length() && isdigit(tokens[i]))
            {
                val = (val*10) + (tokens[i]-'0');
                i++;
            }
            values.push(val);
            i--;
        }
        else if(tokens[i] == ')' || tokens[i] == '}' || tokens[i] == ']')
        {
            while(!ops.isEmpty() && ops.top() != '(' && ops.top() != '{' && ops.top() != '[')
            {
                int val2 = values.top();
                values.pop();
                 
                int val1 = values.top();
                values.pop();
                 
                char op = ops.top();
                ops.pop();
                 
                values.push(applyOp(val1, val2, op));
            }
            if(!ops.isEmpty())
               ops.pop();
        }
        else
        {
            while(!ops.isEmpty() && precedence(ops.top())
                                >= precedence(tokens[i])){
                int val2 = values.top();
                values.pop();
                 
                int val1 = values.top();
                values.pop();
                 
                char op = ops.top();
                ops.pop();
                 
                values.push(applyOp(val1, val2, op));
            }
            ops.push(tokens[i]);
        }
    }
     
    while(!ops.isEmpty()){
        int val2 = values.top();
        values.pop();
                 
        int val1 = values.top();
        values.pop();
                 
        char op = ops.top();
        ops.pop();
                 
        values.push(applyOp(val1, val2, op));
    }
     
    return values.top();
}

int main(int argc, char *argv[]) {
  int neg[100];
  int counter_fornegarray = 0;
  LL sarahs_ll;
  LL alexs_ll;
  LL combined;
  int total_invalid = 0;
  bool check_alex = false;
  bool check_sarah = false;
  bool sarah = false, alex = false;
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream output(am.get("output"));
  string empty = "";
  string password = "";
  if(input.is_open())
  {
    while(!input.eof())
      {
        getline(input >> ws, empty);
        if(empty == "Sarah")
        {
          sarah = true;
          alex = false;
        }
        else if(empty == "Alex")
        {
          alex = true;
          sarah = false;
        }
        else if(empty.substr(0,8) == "Passcode")
          password = empty;
        else
          if(sarah)
          {
            if(hasCorrectBrackets(empty, total_invalid))
            {
              int expressed = evaluate(empty);
              if(expressed >= 0)
              {
                sarahs_ll.insert_atpos(expressed);    
                cout << expressed << endl;
              }
              else if(expressed < 0)
              {
                neg[counter_fornegarray] = expressed;
                counter_fornegarray++;             
              }
            }
          }
 
          else
          {
            if(hasCorrectBrackets(empty, total_invalid))
            {
              int expressed = evaluate(empty);
              if(expressed >= 0)
              {
                alexs_ll.insert_atpos(expressed);    
                cout << expressed << endl;
              }
              else if(expressed < 0)
              {
                neg[counter_fornegarray] = expressed;
                counter_fornegarray++;
              }
            }
          }
      }
    cout << password << endl;
  }
  for(int i = 0; i < counter_fornegarray; i++)
    {
      sarahs_ll.remove_value(neg[i] * -1, check_sarah);
                if(check_sarah)
                {
                  check_sarah = false;
                  continue;
                }
                else
      alexs_ll.remove_value(neg[i] * -1, check_alex);
    }
  
  alexs_ll.reverse();
  sarahs_ll.reverse();
  combined.merge_lists(sarahs_ll, alexs_ll, combined);
  combined.reverse();
  combined.remove_index(total_invalid);
  combined.reverse();
  
  output << "Sarah: ";
  sarahs_ll.print(output);
  output << "Alex: ";
  alexs_ll.print(output);
  output << "Decoded passcode: ";
  combined.print2(output);
  string real_pass;
  
  if(password != "")
  {
      output << "Actual passcode: | ";
      real_pass =  password.substr(9, -1);
      for(int i = 0; i < real_pass.length() - 1; i++)
        {
          output << real_pass[i] << " | ";
        }
      output << real_pass[real_pass.length()-1] << " |";  
  }
  input.close();
  output.close();
}