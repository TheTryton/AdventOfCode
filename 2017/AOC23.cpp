#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <cmath>

using namespace std;

enum class op
{
    set,
    sub,
    mul,
    jnz,
    none
};

struct operation
{
    long long* registera = nullptr;
    long long* registerb = nullptr;
    op oper = op::none;

    int evaluate()
    {
        switch(oper)
        {
        case op::set:
            *registera=(*registerb);
            break;
        case op::sub:
            *registera=(*registera)-(*registerb);
            break;
        case op::mul:
            *registera=(*registera)*(*registerb);
            break;
        case op::jnz:
            if((*registera)!=0)
                return *registerb;
            break;
        }

        return 1;
    }
};

int fromString(string val)
{
    stringstream ss(val);
    int out = 0;
    ss >> out;
    return out;
}

map<string, long long> retrieveRegisters(vector<string> input)
{
    map<string, long long> registers;
    for (string line : input)
    {
        line = line.substr(line.find(' ')+1);

        string registera = line.substr(0,line.find(' '));
        if (registera[0] >= 97 && registera[0]<122)registers[registera] = 0;


        line = line.substr(line.find(' ')+1);
        string registerb = "0";
        if(line!="")registerb = line;
        if (registerb[0] >= 97 && registerb[0]<122)registers[registerb] = 0;
    }

    return registers;
}

vector<operation> translateToOperations(vector<string> input, map<string, long long>& registers)
{
    vector<operation> operations;

    for (string line : input)
    {
        string command = line.substr(0,line.find(' '));

        line = line.substr(line.find(' ')+1);

        string registera = line.substr(0,line.find(' '));

        line = line.substr(line.find(' ')+1);
        string registerb="0";
        if(line!="")registerb=line;

        operation o;

        if(command=="set")
        {
            o.oper = op::set;
        }
        else if(command=="sub")
        {
            o.oper = op::sub;
        }
        else if(command=="mul")
        {
            o.oper = op::mul;
        }
        else if(command=="jnz")
        {
            o.oper = op::jnz;
        }

        if (registera[0] >= 97 && registera[0]<122)
        {
            o.registera = &registers[registera];
        }
        else
        {
            o.registera = new long long(fromString(registera));
        }
        if (registerb[0] >= 97 && registerb[0]<122)
        {
            o.registerb = &registers[registerb];
        }
        else
        {
            o.registerb = new long long(fromString(registerb));
        }

        operations.push_back(o);
    }

    return operations;
}

void setRegisters(map<string, long long>& registers,long long val)
{
    for (auto& reg : registers)
    {
        reg.second=val;
    }
}

size_t firstPart(vector<operation>& operations)
{
    int position = 0;
    size_t mulExecuted = 0;
    while(position>=0&&position<operations.size())
    {
        if(operations[position].oper == op::mul)
        {
            mulExecuted++;
        }
        position += operations[position].evaluate();

    }

    return mulExecuted;
}

bool isPrime(long long num)
{
    if(num%2==0)
        return false;

    for(long long i=3;i<sqrt(num);i+=2)
    {
        if(num%i==0)
            return false;
    }

    return true;
}

int secondPart()
{


    long long b = 106700;
    long long c = 123700;
    long long h = 0;

    for(b=106700;b<c+1;b+=17)
    {
        if(!isPrime(b))
        {
            h++;
        }
    }

    return h;
}

int main()
{
    vector<string> input;
    string line = "";
    do
    {
        line = "";
        getline(cin, line);
        if (line != "")
            input.push_back(line);
    } while (line != "");

    map<string, long long> registers1 = retrieveRegisters(input);

    vector<operation> operations1 = translateToOperations(input, registers1);

    cout << "First part: " << firstPart(operations1) << endl;

    setRegisters(registers1,0);

    cout << "Second part: " << secondPart() << endl;
}

