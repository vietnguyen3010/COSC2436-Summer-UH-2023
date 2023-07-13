#include <iostream>
#include <fstream>
#include <queue>

#include "ArgumentManager.h"
using namespace std;


bool BFS(int **graph, int start, int end, int n)
{
    queue<int> q;
    bool *visited = new bool[n];

    for(int i = 0; i < n; i++)
    {
        visited[i] = false;
    }

    q.push(start);
    int current;

    while(!q.empty()){

        current = q.front();
        q.pop();

        if(current == end){
            delete [] visited;
            return true;
        }

        else if(!visited[current]){
            visited[current] = true;
        }

        for(int i = 0; i < n; i++){
            if(graph[current][i] != 0 && !visited[i]){
                q.push(i);
            }
        }
    }

    delete [] visited;

    return false;
}


int main(int argc, char *argv[]) {

    ArgumentManager am(argc, argv);

    // ifstream input(am.get("input"));
    // ofstream output(am.get("output"));

    ifstream input("input1.txt");
    ofstream output("output.txt");

    int n, start, end;
    input >> n;
    int **graph = new int*[n];

    for(int i = 0; i < n; i++)
    {
        graph[i] = new int[n];
    }

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        graph[i][j] = 0;

    input >> start;
    input >> end;

    string line;

    int i, j = 0;

    while(getline(input, line))
    {
       
        if(line == " " || line.length() == 0)
            continue;

        i = stoi(line.substr(0, line.find(' ')));
        j = stoi(line.substr(line.rfind(' ')));

    }

    graph[i][j] = 1;
    graph[j][i] = 1;

    if(BFS(graph, start, end, n))
    {
        cout << "true" << endl;
        output << "true" << endl;
    }

    else
        cout << "false" << endl;
        output << "false" << endl;

    return 0;
}