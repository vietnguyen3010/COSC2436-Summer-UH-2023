#ifndef cuckookhash_h
#define cuckookhash_h

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
using namespace std;
class CuckooHashTable
{
private:
    vector<int> table1;
    vector<int> table2;
    int size;

public:
    CuckooHashTable(int n)
    {
        size = n;
        table1.resize(size, -1);
        table2.resize(size, -1);
    }

    int hashFunction1(int key, int itr)
    {
        return (key + itr) % size;
    }

    int hashFunction2(int key, int itr)
    {
        return (key * (itr + 1)) % size;
    }

    bool insert(int firstchoice, int secondchoice) 
    {

        if (table1[firstchoice] == -1)
            table1[firstchoice] = 1;
        else if (table1[firstchoice] != -1){
            if (table1[secondchoice] == -1)
                table1[secondchoice] = 1;
            else if (table1[secondchoice] != -1)
                return false;
        }

        // for (int i = 0; i < size; ++i)
        // {
        //     int index1 = hashFunction1(key, i);
        //     if (table1[index1] == -1) 
        //     {
        //         table1[index1] = key;
        //         return true;
        //     }

        //     int index2 = hashFunction2(key, i);
        //     if (table2[index2] == -1) 
        //     {
        //         table2[index2] = key;
        //         return true;
        //     }

        //     if (i == size - 1)
        //         return false;

        //     swap(key, table1[index1]);
        // }

        return true;
    }

        void printTable() {
        std::cout << "Table 1: ";
        for (int i = 0; i < size; ++i) {
            std::cout << table1[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "Table 2: ";
        for (int i = 0; i < size; ++i) {
            std::cout << table2[i] << " ";
        }
        std::cout << std::endl;
    }

};



#endif