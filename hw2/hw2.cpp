#include <iostream>
#include <fstream>
#include "ll.h"
#include "ArgumentManager.h"
using namespace std;


//fdfdf

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);
    // ifstream input(am.get("input"));
    // ofstream output(am.get("output"));
    // ifstream command(am.get("command"));

    ifstream input("input21.txt");
    ofstream output("output21.txt");
    ifstream command("command21.txt");
    string sentence;
    getline(input, sentence);
    ll ll1;
    
    if (sentence == "Alphabetically")
    {
        while (getline(input, sentence))
        {
            if (ll1.checkdup(sentence) == 0)
                ll1.addatend(sentence);
               
        }
        ll1.sortAlphabetically();
    }

    else if (sentence == "Length")
    {
        while (getline(input, sentence))
        {
            if(ll1.checkdup(sentence) == 0)
                ll1.addatend(sentence);
          
        }
        ll1.sortlength();
    }

    else if (sentence == "Beginning")
    {
        while (getline(input, sentence))
        {
            if(ll1.checkdup(sentence) == 0)
                ll1.addatbegin(sentence);
                   
        }
    }

    else if (sentence == "End")
    {
        while (getline(input, sentence))
        {
            if(ll1.checkdup(sentence) == 0)
                ll1.addatend(sentence);
          
                
        }
    }


    while (getline(command, sentence)){
        
            if (sentence.find("Remove") != -1){
                ll1.removesegments(getData(sentence));

            }
            if (sentence.find("Add") != - 1 && ll1.checkdup(getData(sentence)) == 0){
                
                    ll1.addatindex(getData(sentence), getIndex(sentence));
            }
            if (sentence.find("Sort") != - 1){
                if (sentence.find("alphabetically") != - 1){
                    ll1.sortAlphabetically();
                }
                else {
                    ll1.sortlength();
                }
            }
        
    }
    
    ll1.print(output);


}


