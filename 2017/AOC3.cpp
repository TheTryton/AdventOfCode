#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int getSpiral(int number)
{
    return (-3+(int)sqrt(number))/2 + 1;
}

pair<int,int> getPosition(int number)
{
    int spiral = getSpiral(number);
    int spiralNumber = (spiral*2+1)*(spiral*2+1);
    pair<int,int> pos = pair<int,int>(spiral,-spiral);

    if(number == spiralNumber)
    {
        return pos;
    }

    if(number > spiralNumber && number <= spiralNumber + (spiral+1)*2)
    {
        return pair<int,int>(pos.first+1,pos.second+(number - spiralNumber - 1));
    }

    pos = pair<int,int>(pos.first+1,pos.second + (spiral+1)*2 - 1);
    spiralNumber = spiralNumber + (spiral+1)*2;

    if(number > spiralNumber && number <= spiralNumber + (spiral+1)*2)
    {
        return pair<int,int>(pos.first - (number - spiralNumber),pos.second);
    }

    pos = pair<int,int>(pos.first - (spiral+1)*2,pos.second);
    spiralNumber = spiralNumber + (spiral+1)*2;

    if(number > spiralNumber && number <= spiralNumber + (spiral+1)*2)
    {
        return pair<int,int>(pos.first,pos.second - (number - spiralNumber));
    }

    pos = pair<int,int>(pos.first,pos.second - (spiral+1)*2);
    spiralNumber = spiralNumber + (spiral+1)*2;

    if(number > spiralNumber && number < spiralNumber + (spiral+1)*2)
    {
        return pair<int,int>(pos.first + (number - spiralNumber),pos.second);
    }
}

int firstPart(int number)
{
    pair<int,int> position = getPosition(number);
    return abs(position.first) + abs(position.second);
}

int secondPart(int number)
{
    vector<vector<int>> valueMap(129,vector<int>(129,0));

    pair<int,int> pos = pair<int,int>(64,64);

    while(true)
    {
        int sum = 0;

        int valLeft = valueMap[pos.first-1][pos.second];
        int valRight = valueMap[pos.first+1][pos.second];
        int valDown = valueMap[pos.first][pos.second-1];
        int valUp = valueMap[pos.first][pos.second+1];

        int valLeftUp = valueMap[pos.first-1][pos.second+1];
        int valRightUp = valueMap[pos.first+1][pos.second+1];
        int valLeftDown = valueMap[pos.first-1][pos.second-1];
        int valRightDown = valueMap[pos.first+1][pos.second-1];

        sum += valLeft + valRight + valDown + valUp;
        sum += valLeftUp + valRightUp + valLeftDown + valRightDown;

        if(sum == 0){
            sum=1;
            pos = pair<int,int>(pos.first+1,pos.second);
        }

        if(sum>number)return sum;

        valueMap[pos.first][pos.second] = sum;

        //KRAWEDZIE

        if(valLeftDown !=0 && valDown!=0 &&
           valLeft==0 && valRight==0 && valUp==0 &&
           valLeftUp==0 && valRightUp==0 && valRightDown==0){
            pos = pair<int,int>(pos.first-1,pos.second);
            continue;
        }

        if(valLeftDown ==0 && valDown==0 &&
           valLeft==0 && valRight!=0 && valUp==0 &&
           valLeftUp==0 && valRightUp==0 && valRightDown!=0){
            pos = pair<int,int>(pos.first,pos.second-1);
            continue;
        }

        if(valLeftDown ==0 && valDown==0 &&
           valLeft!=0 && valRight==0 && valUp==0 &&
           valLeftUp!=0 && valRightUp==0 && valRightDown==0){
            pos = pair<int,int>(pos.first,pos.second+1);
            continue;
        }

        if(valLeftDown ==0 && valDown==0 &&
           valLeft==0 && valRight==0 && valUp!=0 &&
           valLeftUp==0 && valRightUp!=0 && valRightDown==0){
            pos = pair<int,int>(pos.first+1,pos.second);
            continue;
        }

        //BOKI

        if(valLeft!=0 && valUp==0){
            pos = pair<int,int>(pos.first,pos.second+1);
            continue;
        }

        if(valDown!=0 && valLeft==0){
            pos = pair<int,int>(pos.first-1,pos.second);
            continue;
        }

        if(valRight!=0 && valDown==0){
            pos = pair<int,int>(pos.first,pos.second-1);
            continue;
        }

        if(valUp!=0 && valRight==0){
            pos = pair<int,int>(pos.first+1,pos.second);
            continue;
        }
    }

    return 0;
}

int main()
{
    int input = 0;
    cin >> input;

    cout << firstPart(input) << endl;
    cout << secondPart(input) << endl;
}
