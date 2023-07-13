#include <iostream>
#include "binarytree.h"
#include "ArgumentManager.h"
#include "cuckookhash.h"
#include <string>

using namespace std;

int main(int argc, char *argv[]){
    ArgumentManager am(argc, argv);
    BinaryTree test;
    ifstream input("input22.txt");
    ofstream output("output.txt");
    // ifstream input(am.get("input"));
    // ofstream output(am.get("output"));
    // ifstream command(am.get("command"));
    string x;

    while (x.length() == 0 || x.length() == 1){ //value of newline is 0, value of endline is 1
        getline(input,x);   //getting in m and n
    }
    int m = stoi(x.substr(0,x.find(" ")));
    int n = stoi(x.substr(x.rfind(" ")));
    // cout << "this is m:" <<m<<endl<<"this is n:"<<n<<endl;
    CuckooHashTable nnn(n);
    bool hold = true;
    for (int i = 0; i<m ; i++){
        getline(input,x);
        int aa=stoi(x.substr(0,x.find(" ")));
        int bb=stoi(x.substr(x.rfind(" ")));
         if(!nnn.insert(aa,bb)){
            cout<<"Failed"<<endl;
            output<<"Failed"<<endl;
            hold = false;
         }
    }
    // nnn.printTable();

    if (hold == true){
        cout<<"Passed"<<endl;
        output<<"Passed"<<endl;

        while (getline(input,x) ){

            if(x.length() == 0){}
        
            else {
                // cout << x <<endl;
                    if(x.length() == 5){
                        test.addNode(x);
                    }
                    else if (x.length() == 11) {
                    // cout <<x<<endl;
                    string a= x.substr(0, x.find(" "));
                    string b= x.substr(x.find(" ")+1);
                    cout <<"Looking for: "<<a <<endl <<"Starting from: "<< b <<endl;
                    output <<"Looking for: "<<a <<endl <<"Starting from: "<< b <<endl;
                    cout <<test.treePath(test.getRoot(), stoi(a), 0)<<endl;
                    output <<test.treePath(test.getRoot(), stoi(a), 0)<<endl;
                    test.employeePath(test.find(stoi(b),test.getRoot()),test.find(stoi(a), test.getRoot()), output);
                    }
            }
        }
    }

    // while(getline(input,x)){
    // cout<<x<<endl;}




    // string a= x.substr(0, x.find(" "));
    // string b= x.substr(x.find(" ")+1);
    // cout <<"Looking for: "<<a <<endl <<"Starting from: "<< b <<endl;
    // cout <<test.treePath(test.getRoot(), stoi(a), 0)<<endl;
    // test.employeePath(test.find(stoi(b),test.getRoot()),test.find(stoi(a), test.getRoot()));

    // cout<<x<<endl;
}