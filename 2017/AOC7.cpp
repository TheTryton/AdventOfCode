#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct program
{
    string programName;
    int weight;
    int sumWeight;

    program* parent;
    vector<program*> children;

    program(string programName, int weight)
    {
        this->weight = weight;
        this->programName = programName;
        sumWeight = 0;
        parent=nullptr;
    }
    program()
    {
        this->weight = 0;
        sumWeight = 0;
        this->programName = "";
        parent=nullptr;


    }

    int calcWeight()
    {
        sumWeight = weight;
        for(auto& prog : children)
        {
            sumWeight += prog->calcWeight();
        }

        return sumWeight;
    }
};

map<string, program> parseInput(vector<string>& input)
{
    map<string, program> programs;

    for(string& line : input)
    {
        string programName = line.substr(0,line.find(' '));

        stringstream wt(line.substr(line.find('(')+1,line.find(')')-line.find('(')-1));

        int programWeight = 0;
        wt >> programWeight;

        programs[programName] = program(programName,programWeight);
    }

    for(string& line : input)
    {
        string programName = line.substr(0,line.find(' '));

        if(line.find("->")!=string::npos)
        {
            line = line.substr(line.find("->")+3);

            vector<string> children;
            while(line.size()!=0)
            {
                if(line.find(',')!=string::npos)
                {
                    string child = line.substr(0,line.find(','));
                    line.erase(line.begin(),line.begin() + line.find(',') + 2);
                    children.push_back(child);
                }
                else
                {
                    string child = line;
                    line.clear();
                    children.push_back(child);
                }
            }

            for(string& child : children)
            {
                programs[programName].children.push_back(&programs[child]);
                programs[child].parent = &programs[programName];
            }
        }
    }

    return programs;
}

string firstPart(map<string, program>& programs)
{
    program* prog;

    for(auto& first : programs)
    {
        prog = &first.second;
        break;
    }

    while(prog->parent!=nullptr)
    {
        prog = prog->parent;
    }

    return prog->programName;
}

int secondPart(map<string, program>& programs)
{
    program* prog = &programs[firstPart(programs)];
    prog->calcWeight();

    vector<pair<program*,program*>> unbalancedProgs;

    for(auto& pm : programs)
    {
        map<int,pair<int,program*>> valueSets;

        if(pm.second.children.size() == 0)
            continue;

        for(auto& child : pm.second.children)
        {
            valueSets[child->sumWeight].first++;
            valueSets[child->sumWeight].second = child;
        }

        vector<pair<int,program*>> unbalanced;
        int smallest = INT_MAX;

        for(auto& set : valueSets)
        {
            unbalanced.push_back(pair<int,program*>(set.second.first,set.second.second));
        }

        if(unbalanced.size()==2)
        {
            if(unbalanced[0].first > unbalanced[1].first)
            {
                unbalancedProgs.push_back(pair<program*,program*>(unbalanced[0].second,unbalanced[1].second));
            }
            else
            {
                unbalancedProgs.push_back(pair<program*,program*>(unbalanced[1].second,unbalanced[0].second));
            }
        }
    }

    size_t smallest = 0;
    if(unbalancedProgs.size()==0)
        return 0;

    for(size_t i=0;i<unbalancedProgs.size();i++)
    {
        if(unbalancedProgs[i].first->sumWeight<unbalancedProgs[smallest].first->sumWeight)
        {
            smallest = i;
        }
    }

    return unbalancedProgs[smallest].second->weight - (unbalancedProgs[smallest].second->sumWeight - unbalancedProgs[smallest].first->sumWeight);
}

int main()
{
    string line = "";
    vector<string> input;
    do
    {
        line = "";
        getline(cin,line);
        if(line!="")
        {
            input.push_back(line);
        }
    }
    while(line != "");

    map<string, program> data = parseInput(input);

    cout << "First part: " << firstPart(data) << endl;
    cout << "Second part: " << secondPart(data) << endl;
}
