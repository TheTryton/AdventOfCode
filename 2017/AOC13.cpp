#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int fromString(string val)
{
    stringstream ss(val);
    int out = 0;
    ss >> out;
    return out;
}

vector<int> translateToRanges(vector<string>& input)
{
    vector<int> ranges;
    for(size_t i=0;i<input.size();i++)
    {
        size_t index = fromString(input[i].substr(0,input[i].find(':')));
        size_t range = fromString(input[i].substr(input[i].find(':')+1));
        if(index>ranges.size())
        {
            for(size_t j=ranges.size();j<index;j++)
            {
                ranges.push_back(0);
            }
        }
        ranges.push_back(range);
    }
    return ranges;
}

int findSeverity(vector<int>& ranges,int delay)
{
    int severity = 0;
    for(size_t i=0;i<ranges.size();i++)
    {
        if(ranges[i]!=0)
        {
            int scannerPos = 0;

            if(ranges[i]!=1)
            {
                scannerPos = (i+delay)%((ranges[i]-1)*2);

                if(scannerPos>=ranges[i])
                {
                    scannerPos = 2*ranges[i] - scannerPos - 2;
                }
            }

            if(scannerPos==0)
            {
                severity+=i*ranges[i];
            }
        }
    }
    return severity;
}

int findSeveritySP(vector<int>& ranges, int delay)
{
    int severity = 0;
    for(size_t i=0;i<ranges.size();i++)
    {
        if(ranges[i]!=0)
        {
            int scannerPos = 0;

            if(ranges[i]!=1)
            {
                scannerPos = (i+delay)%((ranges[i]-1)*2);

                if(scannerPos>=ranges[i])
                {
                    scannerPos = 2*ranges[i] - scannerPos - 2;
                }
            }

            if(scannerPos==0)
            {
                severity+=(i+1)*ranges[i];
            }
        }
    }
    return severity;
}

int firstPart(vector<int>& ranges)
{
    return findSeverity(ranges,0);
}

//NOT OPTIMAL
int secondPart(vector<int>& ranges)
{
    int delay = 0;
    while(findSeveritySP(ranges,delay)!=0)
    {
        delay++;
    }
    return delay;
}

int main()
{
    vector<string> input;
    string line;
    do
    {
        line="";
        getline(cin,line);
        if(line!="")
            input.push_back(line);
    }
    while(line!="");

    vector<int> ranges = translateToRanges(input);

    cout << "First part: " << firstPart(ranges) << endl;
    cout << "Second part: " << secondPart(ranges) << endl;
}
