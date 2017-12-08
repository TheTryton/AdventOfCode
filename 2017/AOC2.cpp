#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

vector<int> convertRow(string row)
{
    stringstream rowOfValues(row);
    vector<int> values;
    while(!rowOfValues.eof())
    {
        int value = 0;
        rowOfValues >> value;
        if(rowOfValues.fail())break;
        values.push_back(value);
    }
    return values;
}

int getMinMaxDifference(vector<int>& values)
{
    if(values.size()!=0)
    {
        int min = 0;
        int max = 0;
        for(size_t i=1;i<values.size();i++)
        {
            if(values[i]>values[max])max=i;
            else if(values[i]<values[min])min=i;
        }
        return values[max]-values[min];
    }
    return 0;
}

int first_part(vector<vector<int>>& spreadSheet)
{
    int checkSum = 0;
    for(size_t i=0;i<spreadSheet.size();i++)
    {
        int rowMinMaxDiff = getMinMaxDifference(spreadSheet[i]);
        checkSum+=rowMinMaxDiff;
    }
    return checkSum;
}

int getEvenDividors(vector<int>& values)
{
    for(int i=0;i<values.size();i++){
        for(int j=i+1;j<values.size();j++){
            if(values[j]%values[i]==0)
            {
                return values[j]/values[i];
            }
            else if(values[i]%values[j]==0)
            {
                return values[i]/values[j];
            }
        }
    }
    return 0;
}

int second_part(vector<vector<int>>& spreadSheet)
{
    int checkSum = 0;
    for(size_t i=0;i<spreadSheet.size();i++)
    {
        int output = getEvenDividors(spreadSheet[i]);
        checkSum+=output;
    }
    return checkSum;
}

int main()
{
    vector<vector<int>> spreadSheet;

    while(true)
    {
        string rowOfValues = "";
        getline(cin,rowOfValues);
        vector<int> values = convertRow(rowOfValues);
        if(values.size()==0)break;
        spreadSheet.push_back(values);
    }

    cout << "First part: " << first_part(spreadSheet) << endl;
    cout << "Second part: " << second_part(spreadSheet) << endl;
}
