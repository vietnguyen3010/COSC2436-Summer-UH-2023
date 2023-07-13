#include <iostream>
#include <string>
#include "ArgumentManager.h"
#include <fstream>
#include "dll.h"
#include <sstream>
#include <istream>
#include <algorithm>
#include "stack.h"

using namespace std;


int main(int argc, char *argv[]){
    ArgumentManager am(argc, argv);
    // ifstream input(am.get("input"));
    // ifstream command(am.get("command"));
    // ofstream output(am.get("output"));

    ifstream input("input33.txt");
    ifstream command("command33.txt");
    ofstream output("output.txt");
    string line;

    dll<string> test;

    while (getline(input,line)){
        line.erase(remove(line.begin(), line.end(), ' '), line.end());

        // cout << line << endl;
        test.add2end(line);
    }


    while (getline(command,line)){

        if (line == "printList")
            test.print(output);
        else if (line == "printListBackwards")
            test.printbackwards(output);
        else if (line == "flipReserve")
            test.flipReserve();
        else if (line == "printReserveSize")
            test.printReserveSize(output);
        else if (line == "flipReserve")
            test.flipReserve();
        else if (line == "convertReserve")
            test.convertReserve();
        else if (line == "printReserveTop")
            test.printReserveTop(output);
        else if (line.find ("emptyReserve") != -1){
            string x = line.substr( line.find("(")+1, line.find(")") - line.find("(")-1 );
            test.emptyReserve(x);
        }
        else if (line.find("convertList") != -1){
            string x = line.substr( line.find("(")+1, line.find(")") - line.find("(")-1 );
            test.convertList(x);
        }
        else if (line.find("removeList") != -1){
            string x = line.substr( line.find("(")+1, line.find(")") - line.find("(")-1 );
            test.removeList(x);
        }
        else if (line.find("pushReserve")!= -1){
            string x = line.substr( line.find("(")+1, line.find(")") - line.find("(")-1 );
            test.pushReserve(x);
        }
        else if (line.find("popReserve") != -1){
            string x = line.substr( line.find("(")+1, line.find(")") - line.find("(")-1 );
            test.popReserve(x);
        }

    }


  
}

