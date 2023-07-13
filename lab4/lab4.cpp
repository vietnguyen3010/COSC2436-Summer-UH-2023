#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include "ArgumentManager.h"
using namespace std;

int main(int argc, char *argv[]) 
{
  ArgumentManager am(argc, argv);
  // ifstream input(am.get("input"));
  // ofstream output(am.get("output"));

  ifstream input("input.txt");
  ofstream output("output.txt");

if (input.peek() == EOF)
  return 0;
else
{
  int n;
  input >> n;
  map<string, int> wordsmap;
  string str;
  for (int i = 0; i < n; i++)
  {
    input >> str;
    if (wordsmap.find(str) != wordsmap.end())
        wordsmap[str]++;
    else
        wordsmap[str] = 1;

  }
  input.close();

  for (auto itr = wordsmap.begin(); itr != wordsmap.end(); itr++)
  cout << itr->first << ": " << itr->second << endl;
  // output << itr->first << ": " << itr->second << endl;

  output.close();

  return 0;

  }
}








