#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

enum class op
{
    add,
    sub,
    none
};

enum class cond
{
    equals,
    inequals,
    less,
    lesseq,
    greater,
    greatereq,
    none
};

struct operation
{
    int* registera = nullptr;
    int* registerb = nullptr;
    op oper = op::none;

    int* registerc = nullptr;
    int* registerd = nullptr;
    cond condition = cond::none;

    void evaluate()
    {
        int(*operat)(int a,int b) = nullptr;
        bool(*condit)(int a,int b) = nullptr;

        switch(oper)
        {
        case op::add:
            operat = [](int a,int b)->int{return a+b;};
            break;
        case op::sub:
            operat = [](int a,int b)->int{return a-b;};
            break;
        }



        switch(condition)
        {
        case cond::equals:
            condit = [](int a,int b)->bool{return a==b;};
            break;
        case cond::inequals:
            condit = [](int a,int b)->bool{return a!=b;};
            break;
        case cond::less:
            condit = [](int a,int b)->bool{return a<b;};
            break;
        case cond::lesseq:
            condit = [](int a,int b)->bool{return a<=b;};
            break;
        case cond::greater:
            condit = [](int a,int b)->bool{return a>b;};
            break;
        case cond::greatereq:
            condit = [](int a,int b)->bool{return a>=b;};
            break;
        }

        if(condit(*registerc,*registerd))
            *registera = operat(*registera,*registerb);
    }
};

int fromString(string val)
{
    stringstream ss(val);
    int out = 0;
    ss >> out;
    return out;
}

map<string, int> retrieveRegisters(vector<string> input)
{
    map<string, int> registers;
    for (string& line : input)
    {
        string registera = line.substr(0, line.find(' '));

        string registerb = line.substr(line.find(' ') + 1);
        registerb = registerb.substr(registerb.find(' ') + 1);
        string registerc = registerb;
        registerb = registerb.substr(0, registerb.find(' '));

        registerc = registerc.substr(registerc.find(' ') + 1);
        registerc = registerc.substr(registerc.find(' ') + 1);
        string registerd = registerc;
        registerc = registerc.substr(0, registerc.find(' '));

        registerd = registerd.substr(registerd.find(' ') + 1);
        registerd = registerd.substr(registerd.find(' ') + 1);

        if (registera[0] >= 97 && registera[0]<122)registers[registera] = 0;
        if (registerb[0] >= 97 && registerb[0]<122)registers[registerb] = 0;
        if (registerc[0] >= 97 && registerc[0]<122)registers[registerc] = 0;
        if (registerd[0] >= 97 && registerd[0]<122)registers[registerd] = 0;
    }

    return registers;
}

void clearRegisters(map<string, int>& registers)
{
    for (auto& reg : registers)
    {
        reg.second=0;
    }
}

vector<operation> translateToOperations(vector<string> input, map<string, int>& registers)
{
    vector<operation> operations;
    for (string& line : input)
    {
        string registera = line.substr(0, line.find(' '));

        string registerb = line.substr(line.find(' ') + 1);

        string oper = registerb.substr(0, registerb.find(' '));

        registerb = registerb.substr(registerb.find(' ') + 1);
        string registerc = registerb;
        registerb = registerb.substr(0, registerb.find(' '));

        registerc = registerc.substr(registerc.find(' ') + 1);
        registerc = registerc.substr(registerc.find(' ') + 1);
        string registerd = registerc;
        registerc = registerc.substr(0, registerc.find(' '));

        registerd = registerd.substr(registerd.find(' ') + 1);
        string condition = registerd.substr(0, registerd.find(' '));
        registerd = registerd.substr(registerd.find(' ') + 1);

        operation operS;

        if (registera[0] >= 97 && registera[0] <= 122)
            operS.registera = &registers[registera];
        else
            operS.registera = new int(fromString(registera));

        if (registerb[0] >= 97 && registerb[0] <= 122)
            operS.registerb = &registers[registerb];
        else
            operS.registerb = new int(fromString(registerb));

        if (registerc[0] >= 97 && registerc[0] <= 122)
            operS.registerc = &registers[registerc];
        else
            operS.registerc = new int(fromString(registerc));

        if (registerd[0] >= 97 && registerd[0] <= 122)
            operS.registerd = &registers[registerd];
        else
            operS.registerd = new int(fromString(registerd));

        if (oper == "inc")
        {
            operS.oper = op::add;
        }
        else if (oper == "dec")
        {
            operS.oper = op::sub;
        }

        if (condition == "==")
        {
            operS.condition = cond::equals;
        }
        else if (condition == "!=")
        {
            operS.condition = cond::inequals;
        }
        else if (condition == "<")
        {
            operS.condition = cond::less;
        }
        else if (condition == "<=")
        {
            operS.condition = cond::lesseq;
        }
        else if (condition == ">")
        {
            operS.condition = cond::greater;
        }
        else if (condition == ">=")
        {
            operS.condition = cond::greatereq;
        }

        operations.push_back(operS);
    }

    return operations;
}

int firstPart(vector<operation>& operations, map<string, int>& registers)
{
    for (operation& opr : operations)
    {
        opr.evaluate();
    }

    int maxVal = INT_MIN;

    for (auto& reg : registers)
    {
        if (reg.second>maxVal)
        {
            maxVal = reg.second;
        }
    }

    return maxVal;
}

int secondPart(vector<operation>& operations, map<string, int>& registers)
{
    int maxVal = INT_MIN;

    for (operation& opr : operations)
    {
        opr.evaluate();

        if(*opr.registera > maxVal)
        {
            maxVal = *opr.registera;
        }
    }

    return maxVal;
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

    map<string, int> registers = retrieveRegisters(input);
    vector<operation> operations = translateToOperations(input, registers);

    cout << "First part: " << firstPart(operations, registers) << endl;
    clearRegisters(registers);
    cout << "Second part: " << secondPart(operations, registers) << endl;
}
