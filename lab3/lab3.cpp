#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "ArgumentManager.h"
using namespace std;

struct node
{
  string job;
  double priority;
  node *next;
};

class priorityQueue
{
private:
  int size;
  node *front;
  node *back;
  // vector<node> tasks;
public:
  priorityQueue()
  {
    front = back = nullptr;
    size = 0;
  }
  int getSize() {return size;}

  void enqueue(string, double);
  void dequeue();
  void print(ofstream &output);
  void top();

};

void priorityQueue::enqueue(string j, double p)
{
  node *temp = new node;
  temp->job = j;
  temp->priority = p;
  temp->next = nullptr;

  if (front == nullptr || p < front->priority) // linked list is empty
  {
    temp->next = front;
    front = temp;
  }
  else 
  {
    node *cu = front;
    while (cu->next != nullptr && cu->next->priority <= p)
    {
      cu = cu->next;
    }
    temp->next = cu->next;
    cu->next = temp;
  }
  size++;
}

void priorityQueue::dequeue()
{
  if (front == nullptr) //linked list is empty
    return;
  else 
  {
    node *temp = front;
    front = front->next;
    delete temp;
  }
  size--;
}

void priorityQueue::print(ofstream &output)
{
  node *cu = front;
  if (front == nullptr)
    return;
  while (cu != nullptr)
  {
    cout << cu->job << endl;
    cout << cu->priority << endl;
    // output << cu->job << cu->priority << endl;
    cu = cu->next;
  }
}



int main(int argc, char *argv[]) 
{
  ArgumentManager am(argc, argv);
//   ifstream input(am.get("input"));
//   ofstream output(am.get("output"));

  ifstream input("input2.txt");
  ofstream output("output2.txt");
  if (input.peek() != EOF)
  {
    priorityQueue tasks;
    string str = "";
    double p = 
    while (getline(input, str))
    {
      str.erase(remove(str.begin(), str.end(), '\n'), str.end());
      str.erase(remove(str.begin(), str.end(), '\r'), str.end());
      tasks.enqueue(str, p);
      
   }
    tasks.print(output);
    tasks.dequeue();
  }
} 