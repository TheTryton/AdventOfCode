#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <map>
#include <algorithm>

using namespace std;

enum class dir
{
    n,
    s,
    e,
    w,
};

void addRow(vector<vector<bool>>& map, bool start)
{
    if (start)
    {
        map.insert(map.begin(),vector<bool>(map[0].size()));
    }
    else
    {
        map.push_back( vector<bool>(map[0].size()));
    }
}

void addColumn(vector<vector<bool>>& map, bool start)
{
    if (start)
    {
        for (size_t i = 0; i < map.size(); i++)
        {
            map[i].insert(map[i].begin(),false);
        }
    }
    else
    {
        for (size_t i = 0; i < map.size(); i++)
        {
            map[i].push_back(false);
        }
    }
}

vector<pair<int,int>> parseInput1(vector<string> input)
{
    vector<pair<int, int>> mapVals;
    for (size_t i = 0; i < input.size(); i++)
    {
        for (size_t j = 0; j < input[i].size(); j++)
        {
            if (input[i][j] == '#')
            {
                mapVals.push_back(pair<int, int>(j, i));
            }
        }
    }
    return mapVals;
}

map<pair<int, int>,int> parseInput2(vector<string> input)
{
    map<pair<int, int>, int> mapVals;
    for (size_t i = 0; i < input.size(); i++)
    {
        for (size_t j = 0; j < input[i].size(); j++)
        {
            if (input[i][j] == '#')
            {
                mapVals[pair<int, int>(j, i)] = 2;
            }
        }
    }
    return mapVals;
}

size_t firstPart(vector<pair<int, int>> mapVals, int xs, int ys)
{
    const int COUNT = 10000;

    dir direction = dir::n;
    
    pair<int, int> pos = pair<int, int>(xs, ys);

    size_t infectionCount = 0;

    for (size_t i = 0; i < COUNT; i++)
    { 
        if (find(mapVals.begin(), mapVals.end(), pos) != mapVals.end())
        {
            switch (direction)
            {
            case dir::n:
                direction = dir::e;
                break;
            case dir::s:
                direction = dir::w;
                break;
            case dir::e:
                direction = dir::s;
                break;
            case dir::w:
                direction = dir::n;
                break;
            default:
                break;
            }
        }
        else
        {
            switch (direction)
            {
            case dir::n:
                direction = dir::w;
                break;
            case dir::s:
                direction = dir::e;
                break;
            case dir::e:
                direction = dir::n;
                break;
            case dir::w:
                direction = dir::s;
                break;
            default:
                break;
            }
        }
    
        if (find(mapVals.begin(), mapVals.end(), pos) == mapVals.end())
        {
            infectionCount++;
            mapVals.push_back(pos);
        }
        else
        {
            mapVals.erase(find(mapVals.begin(), mapVals.end(), pos));
        }

        pair<int, int> movementDir = pair<int, int>(0, 0);

        switch (direction)
        {
        case dir::n:
            movementDir = pair<int, int>(0, -1);
            break;
        case dir::s:
            movementDir = pair<int, int>(0, 1);
            break;
        case dir::e:
            movementDir = pair<int, int>(1, 0);
            break;
        case dir::w:
            movementDir = pair<int, int>(-1, 0);
            break;
        default:
            break;
        }

        pos.first += movementDir.first;
        pos.second += movementDir.second;

        
    }

    return infectionCount;
}

size_t secondPart(map<pair<int, int>, int> mapVals, int xs, int ys)
{
    const int COUNT = 10000000;

    dir direction = dir::n;

    pair<int, int> pos = pair<int, int>(xs, ys);

    size_t infectionCount = 0;

    for (size_t i = 0; i < COUNT; i++)
    {
        auto val = mapVals.find(pos);
        if (val != mapVals.end())
        {
            if (val->second == 2)
            {
                switch (direction)
                {
                case dir::n:
                    direction = dir::e;
                    break;
                case dir::s:
                    direction = dir::w;
                    break;
                case dir::e:
                    direction = dir::s;
                    break;
                case dir::w:
                    direction = dir::n;
                    break;
                default:
                    break;
                }
            }
            else if (val->second == 3)
            {
                switch (direction)
                {
                case dir::n:
                    direction = dir::s;
                    break;
                case dir::s:
                    direction = dir::n;
                    break;
                case dir::e:
                    direction = dir::w;
                    break;
                case dir::w:
                    direction = dir::e;
                    break;
                default:
                    break;
                }
            }
        }
        else
        {
            switch (direction)
            {
            case dir::n:
                direction = dir::w;
                break;
            case dir::s:
                direction = dir::e;
                break;
            case dir::e:
                direction = dir::n;
                break;
            case dir::w:
                direction = dir::s;
                break;
            default:
                break;
            }
        }

        if (val == mapVals.end())
        {
            mapVals[pos] = 1;
        }
        else
        {
            if (val->second == 1)
            {
                mapVals[pos]++;
                infectionCount++;
            }
            else if (val->second == 2)
            {
                mapVals[pos]++;
            }
            else if (val->second == 3)
            {
                mapVals.erase(mapVals.find(pos));
            }
        }

        pair<int, int> movementDir = pair<int, int>(0, 0);

        switch (direction)
        {
        case dir::n:
            movementDir = pair<int, int>(0, -1);
            break;
        case dir::s:
            movementDir = pair<int, int>(0, 1);
            break;
        case dir::e:
            movementDir = pair<int, int>(1, 0);
            break;
        case dir::w:
            movementDir = pair<int, int>(-1, 0);
            break;
        default:
            break;
        }

        pos.first += movementDir.first;
        pos.second += movementDir.second;
    }

    return infectionCount;
}

int main() {
    vector<string> input;

    string line = "";
    do
    {
        line = "";
        getline(cin, line);
        if (line != "")
            input.push_back(line);
    } while (line != "");

    vector<pair<int, int>> mapVals1 = parseInput1(input);
    map<pair<int, int>,int> mapVals2 = parseInput2(input);

    cout << "First part: " << firstPart(mapVals1, input[0].size() / 2, input.size() / 2) << endl;
    cout << "Second part: " << secondPart(mapVals2, input[0].size() / 2, input.size() / 2) << endl;

    cin.get();
}