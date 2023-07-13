#include <iostream>
#include <string>
#include "ArgumentManager.h"
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

string deleteSpace(string n)
{
    string s;
    for (int i = 0; i < n.size(); i++)
    {
        if (n[i] != ' ')
        {
            s += n[i]; 
        }
    }
    return s;
}

struct Book
{
    string genre;
    string titlte;
    string author;
    string year;

};

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);
    ifstream input(am.get("input"));
    ofstream output(am.get("output"));
    ifstream command(am.get("command"));

    // ifstream input("input13.txt");
    // ifstream command("command13.txt");
    // ofstream output("output13.txt");
    

    string line;
    vector <Book> books;
    string a1;
    string a2;
    string a3;
    string a4;

    while (getline (input, line))
    {
        line = deleteSpace(line);

        if (line.length() == 0)
        {}      
        else if (line.find("genre") < line.find("title") && line.find("title") < line.find("author") && line.find("author") < line.find("year"))
        {
            //cout<< line.substr(7, line.find(",title:")-7) << " ";
            a1 = line.substr(7, line.find(",title:")-7);

            //cout<< line.substr(line.find("title:")+6, line.find(",author:")-line.find("title:")-6  ) << " ";
            a2 = line.substr(line.find("title:")+6, line.find(",author:")-line.find("title:")-6  );

            //cout << line.substr(line.find(",author:")+8 ,line.find(",year")-line.find(",author:")-8  ) << " ";
            a3 = line.substr(line.find(",author:")+8 ,line.find(",year")-line.find(",author:")-8  );

            //cout<< line.substr( line.find(",year:")+6, line.length()-line.find(",year:")-7 ) << endl;
            a4 = line.substr( line.find(",year:")+6, line.length()-line.find(",year:")-7 );


            books.push_back({a1, a2, a3, a4});



        }   

    }
    vector <string> xg;
    vector <string> xt;
    vector <string> xa;
    vector <string> xy;
    string x;
    string check;

    if (command)
    {
        while (!command.eof())
        {
            getline (command, line);
            stringstream ss(line);
            getline(ss, x, ':');

            if (x == "genre")
            {
                getline(ss, check);
                xg.push_back(check);
                //cout << check << endl;
            }
            else if (x == "title")
            {
                getline(ss, check);
                //cout << check << endl;
                xt.push_back(check);
            }
            else if (x == "author")
            {
                getline(ss, check);
                //cout << check << endl;
                xa.push_back(check);
            }
            else if (x == "year")
            {
                getline(ss, check);
                //cout << check << endl;
                xy.push_back(check);
            }
        }
    }

    vector<Book> bucket1;
    vector<Book> bucket2;
    vector<Book> bucket3;
    vector<Book> bucket4;

    if (xg.size() != 0)
    {
        for (int j = 0; j < books.size(); j++)
        {
            for (int i = 0; i < xg.size() ; i++)
            {
                if (xg[i] == books[j].genre)
                {
                    bucket1.push_back(books[j]);
                }
            }
        }
    }
    else
    {
        bucket1 = books;
    }

    if (xt.size() != 0)
    {
        for (int j = 0; j < bucket1.size(); j++)
        {
            for (int i = 0; i < xt.size() ; i++)
            {
                if (xt[i] == bucket1[j].titlte)
                {
                    bucket2.push_back(bucket1[j]);
                }
            }
        }
    }
    else 
    {
        bucket2 = bucket1;
    }


    if (xa.size() != 0)
    {
        for (int j = 0; j < bucket2.size(); j++)
        {
            for (int i = 0; i < xa.size() ; i++)
            {
                if (xa[i] == bucket2[j].author)
                {
                    bucket3.push_back(bucket2[j]);
                }
            }
        }
    }
    else 
    {
        bucket3 = bucket2;
    }


    if (xy.size() != 0)
    {
        for (int j = 0; j < bucket3.size(); j++)
        {
            for (int i = 0; i < xy.size() ; i++)
            {
                if (xy[i] == bucket3[j].year)
                {
                    bucket4.push_back(bucket3[j]);
                }
            }
        }
    }
    else 
    {
        bucket4 = bucket3;
    }

    for (int i = 0; i < bucket4.size(); i++)
    {
            // cout<<"{genre:"<<bucket4[i].genre << ",title:" << bucket4[i].titlte << ",author:" << bucket4[i].author << ",year:" << bucket4[i].year << "}"<<endl; 
            output<<"{genre:"<<bucket4[i].genre << ",title:" << bucket4[i].titlte << ",author:" << bucket4[i].author << ",year:" << bucket4[i].year << "}"<<endl; 
    }
}
