#include <iostream>
#include <vector>

using namespace std;

int firstPart(size_t input)
{
    const int SIZE = 2017;

    vector<int> spinlockBuffer;
    size_t position = 0;

    spinlockBuffer.push_back(0);

    for(size_t r=0;r<SIZE;r++)
    {
        position=(position+input)%spinlockBuffer.size();
        spinlockBuffer.insert(spinlockBuffer.begin()+position+1,r+1);
        position=(position+1)%spinlockBuffer.size();
    }

    for(size_t i=0;i<spinlockBuffer.size();i++)
    {
        if(spinlockBuffer[i]==SIZE)
        {
            return spinlockBuffer[(i+1)%spinlockBuffer.size()];
        }
    }

    return 0;
}

int secondPart(size_t input)
{
    const int SIZE = 50000000;

    size_t sizeOfSpinlockBuffer = 1;
    size_t position = 0;
    size_t numAfterZero = 0;

    for(size_t r=0;r<SIZE;r++)
    {
        position=(position+input)%sizeOfSpinlockBuffer;
        if(position==0)
        {
            numAfterZero = r+1;
        }
        sizeOfSpinlockBuffer++;
        position=(position+1)%sizeOfSpinlockBuffer;
    }

    return numAfterZero;
}

int main()
{
    int input;
    cin >> input;
    cout << "First part: " << firstPart(input) << endl;
    cout << "Second part: " << secondPart(input) << endl;
}
