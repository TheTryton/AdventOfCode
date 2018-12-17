#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

string load_input()
{
    string in;

    ifstream input;
    input.open("AOC5_in.txt");
    if(input.is_open())
    {
        input >> in;
        input.close();
    }

    return in;
}

string aocp1(string in)
{
    int i=0;
    while(i<in.size() - 1)
    {
        if(in[i] == in[i + 1] + 'a' - 'A' ||
           in[i + 1] == in[i] + 'a' - 'A')
        {
            in.erase(in.begin()+i,in.begin()+i+2);
            if(i!=0)
            {
               i--;
            }
        }
        else
        {
            i++;
        }
    }
    return in;
}

size_t aocp2(string in)
{
    size_t _min = in.size();
    for(char c = 'A'; c <= 'Z'; c++)
    {
        string cpy = in;
        cpy.erase(remove(cpy.begin(),cpy.end(),c),cpy.end());
        cpy.erase(remove(cpy.begin(),cpy.end(),c + 'a' - 'A'),cpy.end());
        cpy = aocp1(cpy);
        if(cpy.size() < _min)
        {
            _min = cpy.size();
        }
    }
    return _min;
}

int main()
{
    auto input = load_input();
    ofstream output;
    output.open("AOC5_out.txt");
    if(output.is_open())
    {
        cout << aocp2(input) << endl;
        output << aocp1(input);
        output.close();
    }


    return 0;
}
