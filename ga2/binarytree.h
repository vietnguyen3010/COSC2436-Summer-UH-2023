#ifndef binarytree_h
#define binarytree_h

#include <fstream>
#include <string>
#include <iostream>
using namespace std;

struct Node {
    int id;
    Node* left;
    Node* right;

    Node(int value) : id(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    Node* root;
    int size;

public:
    BinaryTree() : root(nullptr), size(0) {}

    int getSize() const {
        return size;
    }

    Node* getRoot() const {
        return root;
    }

    bool isEmpty() const {
        return size == 0;
    }

    ~BinaryTree() {
        if (!isEmpty())
            deleteTree(root);
    }

    void addNode(const string& input) {
        int value = stoi(input);
        if (root == nullptr)
            root = new Node(value);
        else
            addNode(value, root);

        size++;
    }

    void addNode(int value, Node* currentNode) {
        if (value < currentNode->id) {
            if (currentNode->left != nullptr)
                addNode(value, currentNode->left);
            else
                currentNode->left = new Node(value);
        }
        else if (value > currentNode->id) {
            if (currentNode->right != nullptr)
                addNode(value, currentNode->right);
            else
                currentNode->right = new Node(value);
        }
    }

    void deleteTree(Node* currentNode) {
        if (currentNode->left != nullptr)
            deleteTree(currentNode->left);
        if (currentNode->right != nullptr)
            deleteTree(currentNode->right);

        delete currentNode;
    }

    Node* find(int value, Node* currentNode) const {
        if (currentNode == nullptr || currentNode->id == value)
            return currentNode;

        if (value < currentNode->id)
            return find(value, currentNode->left);
        else
            return find(value, currentNode->right);
    }

    int treePath(Node* start, int valueToFind, int counter) const {
        if (start == nullptr)
            return -1;

        if (start->id == valueToFind){
            if (counter == 0)
                return counter+1;
            else
                return counter;
        }

        if (valueToFind < start->id)
            return treePath(start->left, valueToFind, counter + 1);
        else
            return treePath(start->right, valueToFind, counter + 1);
    }

    void employeePath(Node* start, Node* endpoint, ofstream &output) const {
        if (start == nullptr || endpoint == nullptr)
            return;

        if (start == endpoint) {
            cout << start->id;
            output<<start->id;
            return;
        }

        cout << start->id << "->";
        output<<start->id<<"->";

        if (endpoint->id < start->id)
            employeePath(start->left, endpoint, output);
        else if (endpoint->id > start->id)
            employeePath(start->right, endpoint, output);
    }
};

#endif





























//  #ifndef binarytree_h
//  #define binarytree_h
//  #include <fstream>
//  #include <string>
//  #include <iostream>
//  using namespace std;
 
//  struct node {
//     int id;
//     node *right = nullptr;
//     node *left = nullptr;
//     node(int id) : left(nullptr), right(nullptr), id(id){} //initialize new node with value and empty branches
//  };

//  class tree{
//     private:
//         node *root;
//         int size;
        
//     public:
        
//         tree(){
//             root = nullptr;
//             size = 0;
            
//         }
//         int getsize(){return size;}
//         node* getroot(){return root;}
//         bool isempty(){
//             return size == 0;
//         }
//         ~tree(){
//             if (!isempty())
//                 deletetree(root);
//         }
//         void addnode(string in){
//             int value = stoi(in);
//             if (root == nullptr)
//                 root->id = value;
//             else
//                 nodeadd(value, getroot());

//         }

//         void nodeadd(int value, node* somewhere ){
//             if (value < somewhere->id){
//                 if (somewhere->left != nullptr)
//                     nodeadd(value, somewhere->left);
//                 else
//                     somewhere->left = new node(value);
//             }
//             else if (value > somewhere->id){
//                 if (somewhere ->right !=nullptr)
//                     nodeadd (value, somewhere->right);
//                 else
//                     somewhere->right = new node (value);
//             }
//         }
//         void deletetree(node *spot){
//             if (spot -> right !=nullptr)
//                 deletetree(spot->right);
//             if (spot -> left != nullptr)
//                 deletetree(spot->left);

//             delete spot;
//         }

//         node* find(int in, node* start){
//             if (isempty())
//                 return nullptr;

//             else if (start->id == in)
//                 return start;
//             else if (in < start->id)
//                 return find(in, start ->left);
//             else if (in > start->id)
//                 return find (in, start ->right);
//             else 
//                 return nullptr;
//         }
//         int count=1;
//         int treepath( node* start, int valuetrying2find, int counter ){
//             if (start->id == valuetrying2find)
//                 return counter;
            
//             else if (valuetrying2find < start->id)
//                 return treepath (start->left, valuetrying2find, count++);
//             else if (valuetrying2find > start->id)
//                 return treepath (start->right, valuetrying2find, count++);
//             else
//                 return -1;
//         }

//         void employeepath(node* start, node* endpoint){
//                 if (start == endpoint){
//                     cout << start->id;
//                 }
//                 cout << start->id;
//                 if (endpoint->id < start->id)
//                     return employeepath(start->left, endpoint);
//                 else if (endpoint->id > start->id)
//                     return employeepath(start->right, endpoint);
//         }

//  };
//  #endif