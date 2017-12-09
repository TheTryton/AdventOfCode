#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>

using namespace std;

int firstPart(string line)
{
    int score = 0;
    int group = 0;
    bool isGarbage = false;
    bool isNegated = false;
    for(size_t i=0;i<line.size();i++)
    {
        if(isGarbage)
        {
            if(line[i]=='!')
            {
                isNegated=!isNegated;
            }
            else
            {
                if(!isNegated)
                {
                    if(line[i]=='>')
                    {
                        isGarbage=false;
                    }
                }
                else
                    isNegated=false;
            }
        }
        else
        {
            if(line[i]=='{')
            {
                group++;
            }
            else if(line[i]=='}')
            {
                score+=group;
                group--;
            }
            else if(line[i]=='<')
            {
                isGarbage = true;
            }
        }
    }
    return score;
}

int secondPart(string line)
{
    int garbageAmount = 0;
    bool isGarbage = false;
    bool isNegated = false;
    for(size_t i=0;i<line.size();i++)
    {
        if(isGarbage)
        {
            if(line[i]=='!')
            {
                isNegated=!isNegated;
            }
            else
            {
                if(!isNegated)
                {
                    if(line[i]=='>')
                    {
                        isGarbage=false;
                    }
                    else
                    {
                        garbageAmount++;
                    }
                }
                else
                    isNegated=false;
            }
        }
        else
        {
            if(line[i]=='<')
            {
                isGarbage = true;
            }
        }
    }
    return garbageAmount;
}

int main()
{
    string fileName;
    cout << "Paste input file name:" << endl;
    getline(cin,fileName);

    ifstream inputFile(fileName);
    string line((std::istreambuf_iterator<char>(inputFile)),std::istreambuf_iterator<char>());

    cout << "First part: " << firstPart(line) << endl;
    cout << "Second part: " << secondPart(line) << endl;
}
