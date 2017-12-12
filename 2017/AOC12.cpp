#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <algorithm>

using namespace std;

template <class V, class E> struct Graph {
    struct Ve;

    struct Ed : E {
        int v;
        Ed(E p, int w) : E(p), v(w) { }
    };

    struct Ve : V, vector<Ed> { };

    vector<Ve> g;
    Graph(int n) : g(n){ }

    void EdgeU(int b,int e, E d = E()) {
        g[b].push_back(Ed(d,e));
        g[e].push_back(Ed(d,b));
    }

    vector<int> SCC(int v)
    {
        vector<bool> visited(g.size());
        queue<int> toVisit;
        vector<int> visitedIndices;
        toVisit.push(v);
        visitedIndices.push_back(v);
        visited[v]=true;
        while(toVisit.size()!=0)
        {
            int currV = toVisit.front();
            toVisit.pop();
            for(size_t i=0;i<g[currV].size();i++)
            {
                if(!visited[g[currV][i].v])
                {
                    toVisit.push(g[currV][i].v);
                    visited[g[currV][i].v]=true;
                    visitedIndices.push_back(g[currV][i].v);
                }
            }
        }
        return visitedIndices;
    }
};

struct em{};

typedef Graph<em,em> DGraph;

int fromString(string val)
{
    stringstream ss(val);
    int out = 0;
    ss >> out;
    return out;
}

vector<int> separateIntoValues(string input)
{
    vector<int> out;
    while(input.size()!=0)
    {
        size_t pos = input.find(',');
        if(pos!=string::npos)
        {
            out.push_back(fromString(input.substr(0,pos)));
            input.erase(input.begin(),input.begin()+pos+1);
        }
        else
        {
            out.push_back(fromString(input));
            input.clear();
        }
    }

    return out;
}

DGraph decodeIntoGraph(vector<string>& input)
{
    DGraph grp(input.size());
    for(size_t i =0;i<input.size();i++)
    {
        string& line = input[i];

        string connections = line.substr(line.find('>')+2);

        vector<int> connVals = separateIntoValues(connections);
        for(int& conn:connVals)
        {
            grp.EdgeU(i,conn);
        }
    }

    return grp;
}

int firstPart(DGraph& graph)
{
    return graph.SCC(0).size();
}

//NOT OPTIMAL
int secondPart(DGraph& graph)
{
    vector<int> visitedVertices;
    int last_index = 0;
    int groups = 0;

    while(visitedVertices.size()!=graph.g.size())
    {
        for(size_t i=last_index+1;i<graph.g.size();i++)
        {
            if(std::find(visitedVertices.begin(), visitedVertices.end(), i) == visitedVertices.end())
            {
                last_index = i;
                break;
            }
        }

        vector<int> nextGrp = graph.SCC(last_index);

        visitedVertices.insert(visitedVertices.end(),nextGrp.begin(),nextGrp.end());
        groups++;
    }

    return groups;
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

    DGraph graph = decodeIntoGraph(input);

    cout << "First part: " << firstPart(graph) << endl;
    cout << "Second part: " << secondPart(graph) << endl;
}


