#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

vector<string> separateIntoCommands(string input)
{
    vector<string> out;
    while(input.size()!=0)
    {
        size_t pos = input.find(',');
        if(pos!=string::npos)
        {
            out.push_back(input.substr(0,pos));
            input.erase(input.begin(),input.begin()+pos+1);
        }
        else
        {
            out.push_back(input);
            input.clear();
        }
    }
    return out;
}

int fromString(string val)
{
    stringstream ss(val);
    int out = 0;
    ss >> out;
    return out;
}

void rotateRight(string& progs,int x)
{
    for(int i=0;i<x;i++)
    {
        char prog = progs[progs.size()-1];
        for(int i=progs.size()-1;i>=0;i--)
        {
            progs[i] = progs[i-1];
        }
        progs[0] = prog;
    }
}

string firstPart(vector<string>& commands)
{
    string programs;
    programs.resize(16);

    for(size_t i=0;i<programs.size();i++)
    {
        programs[i]='a'+i;
    }

    for(auto& command : commands)
    {
        if(command[0]=='s')
        {
            int x = fromString(command.substr(1));
            x=x%programs.size();
            rotateRight(programs,x);
        }
        else if(command[0]=='x')
        {
            size_t a = fromString(command.substr(1,command.find('/')-1));
            size_t b = fromString(command.substr(command.find('/')+1));
            swap(programs[a],programs[b]);
        }
        else if(command[0]=='p')
        {
            size_t a_i = 0;
            size_t b_i;
            for(size_t i=0;i<programs.size();i++)
            {
                if(programs[i]==command[1])
                {
                    a_i=i;
                }
                else if(programs[i]==command[3])
                {
                    b_i = i;
                }
            }
            swap(programs[a_i],programs[b_i]);
        }
    }

    return programs;
}

string secondPart(vector<string>& commands)
{
    string programs;
    programs.resize(16);

    const size_t COUNT = 1000000000;

    for(size_t i=0;i<programs.size();i++)
    {
        programs[i]='a'+i;
    }

    for(unsigned long long ct=0;ct<2;ct++)
    {
        for(auto& command : commands)
        {
            if(command[0]=='s')
            {
                int x = fromString(command.substr(1));
                x=x%programs.size();
                rotateRight(programs,x);
            }
            else if(command[0]=='x')
            {
                size_t a = fromString(command.substr(1,command.find('/')-1));
                size_t b = fromString(command.substr(command.find('/')+1));
                swap(programs[a],programs[b]);
            }
            else if(command[0]=='p')
            {
                size_t a_i = 0;
                size_t b_i;
                for(size_t i=0;i<programs.size();i++)
                {
                    if(programs[i]==command[1])
                    {
                        a_i=i;
                    }
                    else if(programs[i]==command[3])
                    {
                        b_i = i;
                    }
                }
                swap(programs[a_i],programs[b_i]);
            }
        }
    }

    vector<long long int> shifts(programs.size());

    string outProg;
    outProg.resize(programs.size());

    for(size_t i=0;i<shifts.size();i++)
    {
        int j=0;
        for(j=0;j<programs.size();j++)
        {
            if(programs[j]=='a'+i)
            {
                break;
            }
        }
        shifts[i] = (long long)i-(long long)j;
        if(shifts[i]<0)
        {
            shifts[i]+=shifts.size();
        }

        shifts[i]=shifts[i];
    }

    for(size_t i=0;i<COUNT/2-2;i++)
    {
        for(size_t j=0;j<programs.size();j++)
        {
            outProg[(j+shifts[j])%programs.size()] = programs[j];
        }
        if(i%1000000==0)
        {
            cout << i/1e7 << '%' << endl;
        }
    }

    return programs;
}

int main()
{
    string fileName;
    cout << "Paste input file name:" << endl;
    getline(cin,fileName);

    ifstream inputFile(fileName);
    string line((std::istreambuf_iterator<char>(inputFile)),std::istreambuf_iterator<char>());


    vector<string> commands = separateIntoCommands(line);
    cout << "First part: " << firstPart(commands) << endl;
    cout << "Second part: " << secondPart(commands) << endl;
}
