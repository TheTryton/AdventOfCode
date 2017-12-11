#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

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

int sign(int a)
{
    if(a<0)
    {
        return -1;
    }

    return 1;
}

int firstPart(vector<string>& commands)
{
    int x = 0;
    int y = 0;
    int z = 0;
    for(string& command:commands)
    {
        if(command=="n")
        {
            x++;
        }
        else if(command=="s")
        {
            x--;
        }
        else if(command=="ne")
        {
            y--;
            x++;
        }
        else if(command=="sw")
        {
            x--;
            y++;
        }
        else if(command=="nw")
        {
            y++;
        }
        else if(command=="se")
        {
            y--;
        }

        z = -x-y;
    }

    return max(abs(x), max(abs(y),abs(z)));
}

int secondPart(vector<string>& commands)
{
    int x = 0;
    int y = 0;
    int z = 0;

    int furthest = 0;

    for(string& command:commands)
    {
        if(command=="n")
        {
            x++;
        }
        else if(command=="s")
        {
            x--;
        }
        else if(command=="ne")
        {
            y--;
            x++;
        }
        else if(command=="sw")
        {
            x--;
            y++;
        }
        else if(command=="nw")
        {
            y++;
        }
        else if(command=="se")
        {
            y--;
        }

        z = -x-y;

        furthest = max(furthest,(int)max(abs(x), max(abs(y),abs(z))));
    }

    return furthest;
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
