#include <iostream>
#include <string>

using namespace std;

int firstPart(string input)
{
    int checksum = 0;
    for(size_t i = 0;i<input.size();i++)
    {
        if(input[i]==input[(i+1)%input.size()])
        {
            checksum += input[i] - 48;
        }
    }

    return checksum;
}

int secondPart(string input)
{
    int checksum = 0;
    for(size_t i = 0;i<input.size();i++)
    {
        if(input[i]==input[(i+input.size()/2)%input.size()])
        {
            checksum += input[i] - 48;
        }
    }

    return checksum;
}

int main()
{
    string input;
    cin >> input;
    cout << "First part: " << firstPart(input) << endl;
    cout << "Second part: " << secondPart(input) << endl;
}
