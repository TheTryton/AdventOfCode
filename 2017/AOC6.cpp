#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

vector<int> parseInput(string input)
{
    stringstream ss(input);

    vector<int> output;

    do
    {
        int value = 0;
        ss >> value;
        output.push_back(value);
    }
    while(ss.good());

    return output;
}

void redistribute(vector<int>& values, size_t index)
{
    int val = values[index];
    values[index]=0;
    int toRedist = ceil(val / (double)values.size());
    while(val > 0)
    {
        index = (index+1)%values.size();
        values[index] += min(toRedist,val);
        val -= min(toRedist,val);
    }
}

size_t findMax(vector<int>& values)
{
    if(values.size()==0)return 0;
    size_t max = 0;
    for(size_t i=0;i<values.size();i++)
    {
        if(values[i]>values[max])
        {
            max = i;
        }
    }

    return max;
}

bool isLooping(vector<vector<int>>& distributionsBefore,vector<int>& currentDistribution,size_t& loopSize)
{
    for(size_t j=0;j<distributionsBefore.size();j++)
    {
        bool all_k = true;
        loopSize = distributionsBefore.size() - j;
        for(size_t i=0;i<distributionsBefore[j].size();i++)
        {
            if(distributionsBefore[j][i]!=currentDistribution[i])
            {
                all_k=false;
                break;
            }
        }
        if(all_k)
            return true;
    }
    return false;
}

size_t firstPart(vector<int> currentDistribution)
{
    vector<vector<int>> distributions;
    size_t steps = 0;
    size_t loopSize = 0;
    while(!isLooping(distributions,currentDistribution,loopSize))
    {
        distributions.push_back(currentDistribution);
        redistribute(currentDistribution,findMax(currentDistribution));
        steps++;
    }
    return steps;
}

size_t secondPart(vector<int> currentDistribution)
{
    vector<vector<int>> distributions;
    size_t steps = 0;
    size_t loopSize = 0;
    while(!isLooping(distributions,currentDistribution,loopSize))
    {
        distributions.push_back(currentDistribution);
        redistribute(currentDistribution,findMax(currentDistribution));
        steps++;
    }
    return loopSize;
}

int main()
{
    string input;
    getline(cin,input);
    vector<int> values = parseInput(input);
    cout << "First part: " << firstPart(values) << endl;
    cout << "Second part: " << secondPart(values) << endl;
}
