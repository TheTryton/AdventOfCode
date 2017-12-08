#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct elf
{
    elf* nextElf;
    elf* prevElf;
    int index;
};

int firstPart(int input)
{
    vector<elf> elves;
    for(int i=0;i<input;i++)
    {
        elf e;
        e.index = i;
        elves.push_back(e);
    }

    for(int i=0;i<input;i++)
    {
        elves[i].nextElf = &elves[(i+1)%elves.size()];
        elves[(i+1)%elves.size()].prevElf = &elves[i];
    }

    int index = 0;
    int killed = 0;
    elf* start = &elves[0];

    while(killed != input - 1)
    {
        elf* e = start->nextElf;
        start->nextElf = e->nextElf;
        e->nextElf->prevElf = start;
        start = e->nextElf;
        killed++;
    }

    return start->index+1;
}

int secondPart(int input)
{
    vector<int> elves;
    for(int i=0;i<input;i++)
    {
        elves.push_back(i+1);
    }

    int index = 0;

    while(elves.size()!=1)
    {
        int size = elves.size();

        elves.erase(elves.begin() + (int)floor(index+elves.size()/2.0)%elves.size());

        if(index+1>elves.size())
            index--;
        index = (index+1)%elves.size();

        if(elves.size()%1000==0)
            cout << 1.0-elves.size()/(double)input << "%" << endl;
    }

    return elves[0];
}
int main()
{
    int input = 0;
    cin >> input;

    cout << "First part :" << firstPart(input) << endl;
    cout << "First part :" << secondPart(input) << endl;

    for(int i=1;i<32;i++)
    {
        cout << i<<": " << secondPart(i) << endl;
    }
}
