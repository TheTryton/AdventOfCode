#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> disectIntoWords(string sentence)
{
    vector<string> words;
    while(sentence.size()!=0)
    {
        if(sentence[0]==' ')
        {
            sentence.erase(sentence.begin());
        }
        else
        {
            size_t index = sentence.size();
            for(size_t i=0;i<sentence.size();i++)
            {
                if(sentence[i]==' ')
                {
                    index = i;
                    break;
                }
            }


            words.push_back(sentence.substr(0,index));
            if(index==sentence.size())
                break;
            sentence.erase(sentence.begin(),sentence.begin()+index);
        }
    }
    return words;
}

bool areAnagrams(string a,string b)
{
    if(a.size()!=b.size())return false;

    for(int i=0;i<a.size();i++)
    {
        int pos = 0;
        if((pos = b.find(a[i]))!=string::npos)
        {
            b.erase(b.begin()+pos);
        }
        else
        {
            return false;
        }
    }
    return true;
}

int firstPart(vector<string> passphrases)
{
    vector<vector<string>> words;

    for(size_t i=0;i<passphrases.size();i++)
    {
        words.push_back(disectIntoWords(passphrases[i]));
    }

    int correctCounter = 0;

    for(size_t n=0;n<words.size();n++)
    {
        bool stop = false;

        for(size_t i=0;i<words[n].size();i++)
        {
            for(size_t j = i+1;j<words[n].size();j++)
            {
                if(words[n][j]==words[n][i])
                {
                    stop = true;
                    break;
                }
            }
            if(stop)
                break;
        }

        if(!stop)
            correctCounter++;
    }

    return correctCounter;
}

int secondPart(vector<string> passphrases)
{
    vector<vector<string>> words;

    for(size_t i=0;i<passphrases.size();i++)
    {
        words.push_back(disectIntoWords(passphrases[i]));
    }

    int correctCounter = 0;

    for(size_t n=0;n<words.size();n++)
    {
        bool stop = false;

        for(size_t i=0;i<words[n].size();i++)
        {
            for(size_t j = i+1;j<words[n].size();j++)
            {
                if(areAnagrams(words[n][j],words[n][i]))
                {
                    stop = true;
                    break;
                }
            }
            if(stop)
                break;
        }

        if(!stop)
            correctCounter++;
    }

    return correctCounter;
}

int main()
{
    vector<string> input;

    string line;
    do{
        getline(cin,line);
        if(line!="")input.push_back(line);
    }
    while(line!="");


    cout << "First part: " << firstPart(input) << endl;
    cout << "Second part: " << secondPart(input) << endl;
}
