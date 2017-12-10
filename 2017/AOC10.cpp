#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int fromString(string val)
{
    stringstream ss(val);
    int out = 0;
    ss >> out;
    return out;
}

void reverse(vector<int>& array, size_t start, size_t len)
{
    for(size_t i=0;i<len/2;i++)
    {
        swap(array[(start+i)%array.size()],array[(start+len-i-1)%array.size()]);
    }
}

vector<int> translateToLengths(string input)
{
    vector<int> lens;
    while(input.size()!=0)
    {
        int index = input.find(',');
        if(index!=string::npos)
        {
            lens.push_back(fromString(input));
            input.erase(input.begin(),input.begin()+index + 1);
        }
        else
        {
            lens.push_back(fromString(input));
            input.clear();
        }
    }
    return lens;
}

vector<int> translateToLengthsASCII(string input)
{
    vector<int> lens;
    for(size_t i=0;i<input.size();i++)
    {
        lens.push_back(input[i]);
    }

    lens.push_back(17);
    lens.push_back(31);
    lens.push_back(73);
    lens.push_back(47);
    lens.push_back(23);

    return lens;
}

int firstPart(vector<int> lengths)
{
    vector<int> elements(256);

    size_t skip_size = 0;
    size_t position = 0;

    for(size_t i=0;i<elements.size();i++)
    {
        elements[i]=i;
    }

    for(size_t i=0;i<lengths.size();i++)
    {
        reverse(elements,position,lengths[i]);
        position = (position + lengths[i] + skip_size)%elements.size();
        skip_size++;
    }

    return elements[0]*elements[1];
}

string secondPart(vector<int> lengths)
{
    vector<int> elements(256);

    size_t skip_size = 0;
    size_t position = 0;

    for(size_t i=0;i<elements.size();i++)
    {
        elements[i]=i;
    }

    for(size_t c=0;c<64;c++)
    {
        for(size_t i=0;i<lengths.size();i++)
        {
            reverse(elements,position,lengths[i]);
            position = (position + lengths[i] + skip_size)%elements.size();
            skip_size++;
        }
    }

    vector<int> denseHash(elements.size()/16);

    for(size_t i=0;i<elements.size();i+=16)
    {
        for(size_t s=0;s<16;s++)
        {
            denseHash[i/16]=denseHash[i/16]^elements[i+s];
        }
    }

    stringstream finalHash;

    for(size_t s=0;s<denseHash.size();s++)
    {
        stringstream tempStr;
        tempStr << std::hex << denseHash[s];
        string hashCode = tempStr.str();
        if(hashCode.size()==1)
        {
            hashCode='0'+hashCode;
        }
        finalHash << hashCode;
    }

    return finalHash.str();
}


int main()
{
    string input;
    getline(cin,input);
    vector<int> lengths = translateToLengths(input);
    cout << "First part: " << firstPart(lengths) << endl;
    lengths = translateToLengthsASCII(input);
    cout << "Second part: " << secondPart(lengths) << endl;
}
