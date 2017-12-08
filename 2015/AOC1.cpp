#include <iostream>
#include <string>

using namespace std;

int firstPart(string& input)
{
    int floor = 0;
    for(size_t i=0;i<input.size();i++)
    {
        if(input[i]=='(')
        {
            floor++;
        }
        else if(input[i]==')')
        {
            floor--;
        }
    }
    return floor;
}

int main()
{
    string input;
    cin >> input;
    cout << "First part: " << firstPart(input) << endl;
}
