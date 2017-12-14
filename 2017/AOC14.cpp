#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <bitset>

using namespace std;

string toString(int val)
{
    stringstream ss;
    ss << val;
    return ss.str();
}

void reverse(vector<int>& array, size_t start, size_t len)
{
    for(size_t i=0;i<len/2;i++)
    {
        swap(array[(start+i)%array.size()],array[(start+len-i-1)%array.size()]);
    }
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

string hexBin(char c)
{
    // TODO handle default / error
    switch(toupper(c))
    {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
    }
}

vector<int> knotHash(vector<int> lengths)
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

    string hx = finalHash.str();

    vector<int> bits;

    for(size_t i=0;i<hx.size();i++)
    {
        string bin = hexBin(hx[i]);
        for(size_t j=0;j<4;j++)
        {
            bits.push_back(bin[j]-48+97);
        }
    }

    return bits;
}

void floodFill(vector<vector<int>>& vals,int x,int y)
{
    if(x>=0&&x<vals.size())
    {
        if(y>=0&&y<vals[x].size())
        {
            if(vals[x][y]=='b')
            {
                vals[x][y]='a';
                floodFill(vals,x-1,y);
                floodFill(vals,x+1,y);
                floodFill(vals,x,y-1);
                floodFill(vals,x,y+1);
            }
        }
    }
}

int firstPart(string input)
{
    vector<vector<int>> hashArray;
    for(size_t i=0;i<128;i++)
    {
        hashArray.push_back(knotHash(translateToLengthsASCII(input+"-"+toString(i))));
    }

    int used = 0;
    for(size_t i=0;i<hashArray.size();i++)
    {
        for(size_t j=0;j<hashArray[i].size();j++)
        {
            if(hashArray[i][j]=='b')
            {
                used++;
            }
        }
    }

    return used;
}

int secondPart(string input)
{
    vector<vector<int>> hashArray;
    for(size_t i=0;i<128;i++)
    {
        hashArray.push_back(knotHash(translateToLengthsASCII(input+"-"+toString(i))));
    }

    int index = 0;
    for(size_t i=0;i<hashArray.size();i++)
    {
        for(size_t j=0;j<hashArray[i].size();j++)
        {
            if(hashArray[i][j]=='b')
            {
                floodFill(hashArray,i,j);
                index++;
            }
        }
    }

    return index;
}

int main()
{
    string input;
    cin >> input;
    cout << "First part: " << firstPart(input) << endl;
    cout << "Second part: " << secondPart(input) << endl;
}
