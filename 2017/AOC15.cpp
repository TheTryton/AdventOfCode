#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

unsigned long long genA(unsigned long long input)
{
    return (16807*input)%2147483647;
    return (16807*input)%2147483647;
}

unsigned long long genB(unsigned long long input)
{
    return (48271*input)%2147483647;
}

unsigned long long genA2(unsigned long long input)
{
    do
    {
        input = (16807*input)%2147483647;
    }
    while(input%4!=0);

    return input;
}

unsigned long long genB2(unsigned long long input)
{
    do
    {
        input = (48271*input)%2147483647;
    }
    while(input%8!=0);

    return input;
}

int firstPart(unsigned long long startA,unsigned long long startB)
{
    unsigned int bits16equal=0;
    for(unsigned int i=0;i<40000000;i++)
    {
        startA = genA(startA);
        startB = genB(startB);

        if(startA%65536==startB%65536)
            bits16equal++;
    }
    return bits16equal;
}

int secondPart(unsigned long long startA,unsigned long long startB)
{
    unsigned int bits16equal=0;
    for(unsigned int i=0;i<5000000;i++)
    {
        startA = genA2(startA);
        startB = genB2(startB);

        if(startA%65536==startB%65536)
            bits16equal++;
    }
    return bits16equal;
}

int main()
{
    unsigned long long startA,startB;
    cin >> startA >> startB;
    cout << "First part: " << firstPart(startA,startB) << endl;
    cout << "Second part: " << secondPart(startA,startB) << endl;
}
