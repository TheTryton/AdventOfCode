#include <iostream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

enum class op
{
    set,
    add,
    mul,
    mod,
    rcv,
    jgz,
    snd,
    none
};

struct operation
{
    long long* registera = nullptr;
    long long* registerb = nullptr;
    op oper = op::none;

    int evaluate(vector<int>& freqs,bool& check_frq)
    {
        switch(oper)
        {
        case op::snd:
            freqs.push_back(*registera);
            break;
        case op::set:
            *registera=(*registerb);
            break;
        case op::add:
            *registera=(*registera)+(*registerb);
            break;
        case op::mul:
            *registera=(*registera)*(*registerb);
            break;
        case op::mod:
            *registera=(*registera)%(*registerb);
            break;
        case op::rcv:
            if((*registera)!=0)
                check_frq=true;
            break;
        case op::jgz:
            if((*registera)>0)
                return *registerb;
            break;
        }

        return 1;
    }

    int evaluate2(vector<int>& messages_out,vector<int>& messages_in)
    {
        switch(oper)
        {
        case op::snd:
            messages_out.push_back(*registera);
            break;
        case op::set:
            *registera=(*registerb);
            break;
        case op::add:
            *registera=(*registera)+(*registerb);
            break;
        case op::mul:
            *registera=(*registera)*(*registerb);
            break;
        case op::mod:
            *registera=(*registera)%(*registerb);
            break;
        case op::rcv:
            if(messages_in.size()==0)
            {
                return 0;
            }
            else
            {
                *registera = messages_in[0];
                messages_in.erase(messages_in.begin());
            }
            break;
        case op::jgz:
            if((*registera)>0)
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

void setRegisters(map<string, long long>& registers,long long val)
{
    for (auto& reg : registers)
    {
        reg.second=val;
    }
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
        else if(command=="add")
        {
            o.oper = op::add;
        }
        else if(command=="mul")
        {
            o.oper = op::mul;
        }
        else if(command=="mod")
        {
            o.oper = op::mod;
        }
        else if(command=="rcv")
        {
            o.oper = op::rcv;
        }
        else if(command=="jgz")
        {
            o.oper = op::jgz;
        }
        else if(command=="snd")
        {
            o.oper = op::snd;
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

int firstPart(vector<operation>& operations)
{
    int position = 0;
    vector<int> frequencies;
    while(position>=0&&position<operations.size())
    {
        bool check_frq = false;
        position += operations[position].evaluate(frequencies,check_frq);
        if(check_frq)
        {
            return frequencies[frequencies.size()-1];
        }
    }

    return 0;
}

int secondPart(vector<operation>& operations1,vector<operation>& operations2)
{
    int position1 = 0;
    int position2 = 0;
    bool fs = false;

    bool dead1=false;
    bool dead2=false;
    vector<int> messages1;
    vector<int> messages2;

    int sentCount = 0;

    while(
          (position1>=0&&position1<operations1.size())||
          (position2>=0&&position2<operations2.size())
          )
    {
        if(dead1&&dead2)break;

        if(fs)
        {
            int offset = operations1[position1].evaluate2(messages1,messages2);

            if(offset==0)
            {
                dead1 = true;
            }
            else
            {
                dead1 = false;
            }
            position1+=offset;
        }
        else
        {
            int msg_count = messages2.size();
            int offset = operations2[position2].evaluate2(messages2,messages1);

            if(msg_count!=messages2.size())
            {
                sentCount++;
            }

            if(offset==0)
            {
                dead2 = true;
            }
            else
            {
                dead2 = false;
            }

            position2+=offset;
        }

        fs=!fs;
    }

    return sentCount;
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
    map<string, long long> registers2 = retrieveRegisters(input);

    vector<operation> operations1 = translateToOperations(input, registers1);
    vector<operation> operations2 = translateToOperations(input, registers2);

    cout << "First part: " << firstPart(operations1) << endl;

    setRegisters(registers1,0);
    setRegisters(registers2,1);

    cout << "Second part: " << secondPart(operations1,operations2) << endl;
}
