#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <map>

using namespace std;

// LONGEST GRAPH

//struct

int fromString(string val)
{
    stringstream ss(val);
    int out = 0;
    ss >> out;
    return out;
}

vector<pair<int,int>> parseInput(vector<string> input)
{
    vector<pair<int,int>> portPairs;
    for(auto& line : input)
    {
        pair<int,int> portPair;
        portPair.first = fromString(line);
        portPair.second = fromString(line.substr(line.find('/')+1));
        portPairs.push_back(portPair);
    }
    return portPairs;
}

int firstPart(vector<pair<int,int>> portPairs)
{
    vector<pair<int,int>> startingPairs;

    map<int,bool>


    for(auto& portPair : portPairs)
    {

    }
}
