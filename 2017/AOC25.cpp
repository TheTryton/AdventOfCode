#include <iostream>
#include <vector>

using namespace std;

struct tape
{
    tape* next = nullptr;
    tape* prev = nullptr;
    bool value = false;
};

size_t firstPart()
{
    tape* furthestLeft = nullptr;

    char state = 'A';
    tape* values = new tape();
    const size_t COUNT = 12656374;
    for(size_t i=0;i<COUNT;i++)
    {
        int mov = 0;

        switch(state)
        {
        case 'A':
            if(!values->value)
            {
                values->value = 1;
                mov = 1;
                state = 'B';
            }
            else
            {
                values->value = 0;
                mov = -1;
                state = 'C';
            }
            break;
        case 'B':
            if(!values->value)
            {
                values->value = 1;
                mov = -1;
                state = 'A';
            }
            else
            {
                values->value = 1;
                mov = -1;
                state = 'D';
            }
            break;
        case 'C':
            if(!values->value)
            {
                values->value = 1;
                mov = 1;
                state = 'D';
            }
            else
            {
                values->value = 0;
                mov = 1;
                state = 'C';
            }
            break;
        case 'D':
            if(!values->value)
            {
                values->value = 0;
                mov = -1;
                state = 'B';
            }
            else
            {
                values->value = 0;
                mov = 1;
                state = 'E';
            }
            break;
        case 'E':
            if(!values->value)
            {
                values->value = 1;
                mov = 1;
                state = 'C';
            }
            else
            {
                values->value = 1;
                mov = -1;
                state = 'F';
            }
            break;
        case 'F':
            if(!values->value)
            {
                values->value = 1;
                mov = -1;
                state = 'E';
            }
            else
            {
                values->value = 1;
                mov = 1;
                state = 'A';
            }
            break;
        }

        if(mov<0)
        {
            if(!values->prev)
            {
                values->prev = new tape();
                values->prev->next = values;
            }

            values = values->prev;

            if(!values->prev)
            {
                furthestLeft = values;
            }
        }

        if(mov>0)
        {
            if(!values->next)
            {
                values->next = new tape();
                values->next->prev = values;
            }

            values = values->next;
        }
    }

    size_t countOnes = 0;

    while(furthestLeft)
    {
        if(furthestLeft->value)
        {
            countOnes++;
        }
        furthestLeft=furthestLeft->next;
    }

    return countOnes;
}

int main()
{
    cout << "First part: " << firstPart() << endl;
}
