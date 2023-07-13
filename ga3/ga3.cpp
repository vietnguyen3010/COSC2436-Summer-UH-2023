#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "graph.h"
#include "ArgumentManager.h"

using namespace std;


int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);
    // ifstream input(am.get("input"));
    // ofstream output(am.get("output"));

    ifstream input("input33.txt");
    ofstream output("output.txt");

    int size, start, end, vert1, vert2, length;
    input >> size;
    bool end_check = false;
    int array[size][size];

    while(!input.eof())
      {
        input >> vert1 >> vert2 >> length;
        // array[vert1][vert2] = length;
        // array[vert2][vert1] = length;   

        cout << vert1 << vert2 << length << endl;

        graph g;
        

      }


}