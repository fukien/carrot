#include "test.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

//using namespace std;

void Test::open(char *filename)
{
    file = new ifstream(filename);
}

vector<string> Test::findNext(vector<string> &mp)
{
    //vector<string> mp;
    string line;
    if (*file)
    {
        if (getline((*file), line))
        {
            int startpos = 0;

            for (int i = 0; i < line.length(); i++)
            {
                if (line[i] == '|')
                {
                    mp.push_back(line.substr(startpos, i - 1));
                    startpos = i + 1;
                }
            }

            mp.push_back(line.substr(startpos, line.length() - 1));
        }
    }
    return mp;
}

void Test::close()
{
    //cout<<"begin close"<<endl;
    (*file).close();
    delete file;
}
