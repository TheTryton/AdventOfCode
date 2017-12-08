#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int parseInt(string text)
{
    stringstream ss(text);
    int out = 0;
    ss >> out;
    return out;
}

vector<int> translate(vector<string> rows)
{
    vector<int> commands;
    for(string row : rows)
    {
        commands.push_back(parseInt(row));
    }
    return commands;
}

size_t firstPart(vector<int> jumpCommands)
{
    int position = 0;
    size_t steps = 0;

    while(position>=0&&position<jumpCommands.size())
    {
        position += jumpCommands[position]++;
        steps++;
    }
    return steps;
}

size_t secondPart(vector<int> jumpCommands)
{
    int position = 0;
    size_t steps = 0;

    while(position>=0&&position<jumpCommands.size())
    {
        int offset = jumpCommands[position];
        if(offset>=3)
        {
            jumpCommands[position]--;
        }
        else
        {
            jumpCommands[position]++;
        }
        position += offset;
        steps++;
    }
    return steps;
}

int main()
{
    vector<string> commands;
    string input;
    do
    {
        input="";
        getline(cin,input);
        if(input!="")
            commands.push_back(input);
    }
    while(input!="");

    cout << "First part: " << firstPart(translate(commands)) << endl;
    cout << "Second part: " << secondPart(translate(commands)) << endl;
}
