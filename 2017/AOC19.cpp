#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

enum direction
{
    north,
    south,
    west,
    east
};

string firstPart(vector<string>& input)
{
    pair<int,int> position = pair<int,int>(0,0);

    position.first = input[0].find('|');

    string lettersInOrder = "";
    direction dir = south;

    while(true)
    {
        if(input[position.second][position.first]>=65&&input[position.second][position.first]<=90)
        {
            lettersInOrder.push_back(input[position.second][position.first]);
        }

        if(input[position.second][position.first] == '+')
        {
            switch(dir)
            {
            case north:
            case south:
                if(input[position.second][position.first+1]!=' ')
                {
                    dir = east;
                }
                else if(input[position.second][position.first-1]!=' ')
                {
                    dir = west;
                }
                else
                {
                    return lettersInOrder;
                }
                break;
            case west:
            case east:
                if(input[position.second+1][position.first]!=' ')
                {
                    dir = south;
                }
                else if(input[position.second-1][position.first]!=' ')
                {
                    dir = north;
                }
                else
                {
                    return lettersInOrder;
                }
                break;
            }
        }

        if(input[position.second][position.first]>=65&&input[position.second][position.first]<=90)
        {
            switch(dir)
            {
            case north:
                if(input[position.second+1][position.first]!=' ')
                {
                    dir = north;
                }
                else if(input[position.second][position.first+1]!=' ')
                {
                    dir = east;
                }
                else if(input[position.second][position.first-1]!=' ')
                {
                    dir = west;
                }
                else
                {
                    return lettersInOrder;
                }
                break;
            case south:
                if(input[position.second-1][position.first]!=' ')
                {
                    dir = south;
                }
                else if(input[position.second][position.first+1]!=' ')
                {
                    dir = east;
                }
                else if(input[position.second][position.first-1]!=' ')
                {
                    dir = west;
                }
                else
                {
                    return lettersInOrder;
                }
                break;
            case west:
                if(input[position.second][position.first-1]!=' ')
                {
                    dir = west;
                }
                else if(input[position.second+1][position.first]!=' ')
                {
                    dir = south;
                }
                else if(input[position.second-1][position.first]!=' ')
                {
                    dir = north;
                }
                else
                {
                    return lettersInOrder;
                }
                break;
            case east:
                if(input[position.second][position.first+1]!=' ')
                {
                    dir = east;
                }
                else if(input[position.second+1][position.first]!=' ')
                {
                    dir = south;
                }
                else if(input[position.second-1][position.first]!=' ')
                {
                    dir = north;
                }
                else
                {
                    return lettersInOrder;
                }
                break;
            }
        }

        switch(dir)
        {
        case north:
            position.second--;
            break;
        case south:
            position.second++;
            break;
        case west:
            position.first--;
            break;
        case east:
            position.first++;
            break;
        }
    }
}

int secondPart(vector<string>& input)
{
    pair<int,int> position = pair<int,int>(0,0);

    position.first = input[0].find('|');

    int steps = 1;
    direction dir = south;

    while(true)
    {
        if(input[position.second][position.first] == '+')
        {
            switch(dir)
            {
            case north:
            case south:
                if(input[position.second][position.first+1]!=' ')
                {
                    dir = east;
                }
                else if(input[position.second][position.first-1]!=' ')
                {
                    dir = west;
                }
                else
                {
                    return steps;
                }
                break;
            case west:
            case east:
                if(input[position.second+1][position.first]!=' ')
                {
                    dir = south;
                }
                else if(input[position.second-1][position.first]!=' ')
                {
                    dir = north;
                }
                else
                {
                    return steps;
                }
                break;
            }
        }

        if(input[position.second][position.first]>=65&&input[position.second][position.first]<=90)
        {
            switch(dir)
            {
            case north:
                if(input[position.second+1][position.first]!=' ')
                {
                    dir = north;
                }
                else if(input[position.second][position.first+1]!=' ')
                {
                    dir = east;
                }
                else if(input[position.second][position.first-1]!=' ')
                {
                    dir = west;
                }
                else
                {
                    return steps;
                }
                break;
            case south:
                if(input[position.second-1][position.first]!=' ')
                {
                    dir = south;
                }
                else if(input[position.second][position.first+1]!=' ')
                {
                    dir = east;
                }
                else if(input[position.second][position.first-1]!=' ')
                {
                    dir = west;
                }
                else
                {
                    return steps;
                }
                break;
            case west:
                if(input[position.second][position.first-1]!=' ')
                {
                    dir = west;
                }
                else if(input[position.second+1][position.first]!=' ')
                {
                    dir = south;
                }
                else if(input[position.second-1][position.first]!=' ')
                {
                    dir = north;
                }
                else
                {
                    return steps;
                }
                break;
            case east:
                if(input[position.second][position.first+1]!=' ')
                {
                    dir = east;
                }
                else if(input[position.second+1][position.first]!=' ')
                {
                    dir = south;
                }
                else if(input[position.second-1][position.first]!=' ')
                {
                    dir = north;
                }
                else
                {
                    return steps;
                }
                break;
            }
        }

        switch(dir)
        {
        case north:
            position.second--;
            break;
        case south:
            position.second++;
            break;
        case west:
            position.first--;
            break;
        case east:
            position.first++;
            break;
        }

        steps++;
    }
}

int main()
{
    vector<string> input;

    string fileName;
    cout << "Paste input file name:" << endl;
    getline(cin,fileName);

    ifstream inputFile(fileName);

    string line = "";
    do
    {
        line = "";
        getline(inputFile, line);
        if (line != "")
            input.push_back(line);
    } while (line != "");

    cout << "First part: " << firstPart(input) << endl;
    cout << "Second part: " << secondPart(input) << endl;
}
