// #include <iostream>
// #include <string>
// #include "ArgumentManager.h"
// #include <fstream>
// #include <sstream>
// #include <algorithm>
// #include <istream>


// using namespace std;

// int main(int argc, char *argv[])
// {
//     ArgumentManager am(argc, argv);
//     // ifstream input(am.get("input"));
//     // ifstream command(am.get("command"));
//     // ofstream output(am.get("output"));

//     ifstream input("input42.txt");
//     // ifstream command("command41.txt");
//     ofstream output("output.txt");


//     while (input.peek() != EOF)
//     {
//         string line = "";
//         input >> line;
//         cout << line;

//     }


// }



#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "ArgumentManager.h"
using namespace std;

int analyze_command(string cmd){// return degree
    string result;

    result = cmd.substr(cmd.find("=")+1);

    return stoi(result);
}

int analyze_level(string level){// return level
    string result;

    result = level.substr(level.find(" ")+1);
    return stoi(result);
}

struct node{
    int *keys; // An array of keys
    node **childptr; // An array of child pointers
    bool leaf; // Is true when node is leaf. Otherwise false
    int size; // Current number of keys

    node(int degree){
        keys = new int[degree];
        childptr = new node*[degree + 1];
        leaf = true;
        size = 0;

        for(int i = 0; i < degree; i++){
            keys[i] = -1;
        }

        for(int i = 0; i < degree + 1; i++){
            childptr[i] = nullptr;  
        }
    }

    int height(node *parent, int h);
    void printLevel(node *parent, int level, ofstream& out);
    node *search(node* parent, int data);
};


class bTree{
    private:
        node *root; // Pointer to root node
        int degree; // Minimum degree

    public:
        bTree(int _degree) 
        {
            root = nullptr;
            degree = _degree;
        }

        void insert(int data){
            if(root == nullptr){
                root = new node(degree);
                root -> keys[0] = data;
                root -> size = 1;
            }
            
            else{
                if(search(data) == NULL){
                    addAtLeaf(nullptr, root, data);
                }
            }
        }

        void addAtLeaf(node *parent, node *n, int data){
            if(n -> leaf){
                int i = n -> size;
                while(i != 0 && n -> keys[i - 1] > data){
                    n -> keys[i] = n -> keys[i - 1];
                    i--;
                }

                n -> keys[i] = data;
                n -> size += 1;
            }

            else{
                int i = 0;
                while(i < n -> size && data > n -> keys[i]){
                    i++;
                }

                addAtLeaf(n, n -> childptr[i], data);
            }

            if(n -> size == degree){
                if(n == root){
                    node* temp = new node(degree);
                    temp -> leaf = false;
                    temp -> childptr[0] = n;
                    splitChild(temp, n);
                    root = temp;
                }

                else{
                    splitChild(parent, n);
                }
            }
        }

    void splitChild(node* parent, node* leftNode){

        node* rightNode = new node(degree);
        rightNode->leaf = leftNode->leaf;
        int mid = (degree - 1) / 2;

        // copy half of left node to right node
        int j = 0;
        for (int i = mid+1; i < degree; i++){
            rightNode->keys[j] = leftNode->keys[i];
            leftNode->keys[i] = -1;
            rightNode->size+=1;  
            leftNode->size-=1;
            j++;
        }

        // copy half the pointer of the left node to the right node
        if (!leftNode->leaf) {
            int childMid = (degree+1) / 2;
            j = 0;
            for (int i = childMid; i < degree+1; i++) {
                rightNode->childptr[j] = leftNode->childptr[i];
                leftNode->childptr[i] = nullptr;
                j++;
            }
        }

        // finding correct index to add the right node
        for (int i = 0; i < degree + 1; i++) {
            if (parent->childptr[i] == leftNode) {
                int j = degree;
                while (j > i + 1) {
                    parent->childptr[j] = parent->childptr[j-1];
                    j--;
                }
                parent->childptr[j] = rightNode;
                break;
            }
        }

        // adding mid key into parent keys
        int i = parent->size;
        while (i != 0 && parent->keys[i-1] > leftNode->keys[mid]) {
            parent->keys[i] = parent->keys[i-1];
            i--;
        }
        parent->keys[i] = leftNode->keys[mid];
        parent->size += 1;
        leftNode->keys[mid] = -1;
        leftNode->size -=1;
    }

    // i need a search function, print level and complete split child function

    int height(){
        return root->height(root, 1);
    }

    void printLevel(int level, ofstream& out){
        root->printLevel(root, level, out);
    }

    node* search(int data){
        return root->search(root, data);
    }
};

    // height function, save height to result
    // or use while loop to update height increment
    int node::height(node *parent, int h){
        if(parent->leaf){
            return h;
        }
        height(parent->childptr[0], h+1);
    }

    //printing level function
    void node::printLevel(node *parent, int level, ofstream& out){
        if(level > 1 && parent->leaf){
            return;
        }
        else if(level == 1){
            for(int i = 0; i < parent->size; i++){
                out<<parent->keys[i]<<" ";
                cout<<parent->keys[i]<<" ";

            }
        }
        else{
            for(int i= 0; i<= parent->size; i++){
                printLevel(parent->childptr[i], level-1, out);
            }
        }
    }

    //search function, return true if found, and else otherwise
    // also, can use vanilla traverse function and modify it
    node* node::search(node* parent, int data){
        int i = 0;

        // Find the first key greater than or equal to data
        while(i < parent->size && data > parent->keys[i]){
            i++;
        }

        if(parent->keys[i] == data){
            return parent;
        }

        if(parent->leaf == true){
            return NULL;
        }

        return search(parent->childptr[i], data);
    }

int main(int argc, char** argv){
    ifstream input("input42.txt");
    ifstream command("command42.txt");
    ofstream output("output41.txt");

    ArgumentManager am(argc, argv);
    // ifstream input(am.get("input"));
    // ifstream command(am.get("command"));
    // ofstream output(am.get("output"));

    int n;
    string cmd, level;
    int degree, levelNum;
    vector<int> numVect, levelVect;

    // getting input
    while(input>>n){
        numVect.push_back(n);
    }

    //getting command
    command >> cmd;
    command.ignore();
    while(getline(command, level)){
        level.erase(remove(level.begin(), level.end(), '\n'), level.end());
        level.erase(remove(level.begin(), level.end(), '\r'), level.end());
        levelVect.push_back(analyze_level(level));
    }

    degree = analyze_command(cmd);

    bTree tree(degree);
    
    //inserting input to tree
    for(int i = 0; i < numVect.size(); i++){
        tree.insert(numVect[i]);
    }

    //output height
    output<<"Height="<<tree.height()<<endl;
    cout <<"Height="<<tree.height()<<endl;

    //outputing the tree
    for(int i=0; i< levelVect.size(); i++){
        if(levelVect[i] > tree.height()){
            output<<"Empty"<<endl;
            cout <<"Empty"<<endl;

        }else{
            tree.printLevel(levelVect[i], output);
            output<<endl;
            cout <<endl;

        }
    }

    return 0;
}