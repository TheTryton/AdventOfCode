#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct vertex
{
    vector<vertex*> child;
    vector<vertex*> parents;
    bool done = false;
    bool working = false;
    char c;
};

struct graph
{
    map<char,vertex> vertices;
    void add_edge(char v_from, char v_to)
    {
        vertices[v_from].c = v_from;
        vertices[v_to].c = v_to;
        auto vf = &vertices[v_from];
        auto vt = &vertices[v_to];
        vf->child.push_back(vt);
        vt->parents.push_back(vf);
    }
};

pair<char,char> parse_e(string a)
{
    pair<char,char> edge;
    auto first_step = a.find("tep ");
    a = a.substr(first_step+4);
    edge.first = a[0];
    auto second_step = a.find("tep ");
    a = a.substr(second_step+4);
    edge.second = a[0];
    return edge;
}

graph load_input()
{
    graph g;

    ifstream input;
    input.open("AOC7_in.txt");
    if(input.is_open())
    {
        while(!input.eof())
        {
            string line;
            getline(input, line);
            if(!line.empty())
            {
                auto e = parse_e(line);
                g.add_edge(e.first, e.second);
            }
        }
        input.close();
    }

    return g;
}

vertex* find_first_ready(graph& g)
{
    vertex* curr_vertex = nullptr;
    char curr_vertex_c = 'Z'+1;

    for(auto& v: g.vertices)
    {
        if(!v.second.done)
        {
            if(v.second.parents.size() == 0 ||
               all_of(v.second.parents.begin(),v.second.parents.end(),[](const vertex* p){
                        return p->done;
                      }))
            {
                if(curr_vertex_c > v.first)
                {
                    curr_vertex = &(v.second);
                    curr_vertex_c = v.first;
                }
            }
        }
    }
    return curr_vertex;
}

string aoc7p1(graph& g)
{
    string output;
    while(auto v = find_first_ready(g))
    {
        output += v->c;
        v->done = true;
    }
    return output;
}

struct worker
{
    int time_left = 0;
    vertex* c_w_v = nullptr;
};

vertex* find_first_ready_workers(graph& g)
{
    vertex* curr_vertex = nullptr;
    char curr_vertex_c = 'Z'+1;

    for(auto& v: g.vertices)
    {
        if(!v.second.done && !v.second.working)
        {
            if(v.second.parents.size() == 0 ||
               all_of(v.second.parents.begin(),v.second.parents.end(),[](const vertex* p){
                        return p->done;
                      }))
            {
                if(curr_vertex_c > v.first)
                {
                    curr_vertex = &(v.second);
                    curr_vertex_c = v.first;
                }
            }
        }
    }
    return curr_vertex;
}

bool graph_done(const graph& g)
{
    return all_of(g.vertices.begin(),g.vertices.end(),[](const auto& v){return v.second.done;});
}

size_t aoc7p2(graph& g)
{
    string out;

    vector<worker> workers(5);

    int time = 0;


    while(!graph_done(g))
    {
        for(auto& w : workers)
        {
            if(!w.c_w_v)
            {
                if(auto v = find_first_ready_workers(g))
                {
                    v->working = true;
                    w.c_w_v = v;
                    w.time_left = v->c - 'A' + 61;
                }
            }
        }
        time++;
        for(auto& w : workers)
        {
            if(w.time_left != 0)
            {
                w.time_left--;
            }
            if(w.time_left == 0 && w.c_w_v)
            {
                w.c_w_v->done = true;
                out += w.c_w_v->c;
                w.c_w_v = nullptr;
            }
        }

    }
    cout << out << endl;
    return time;
}

int main()
{
    auto g = load_input();

    ofstream output;
    output.open("AOC7_out.txt");
    if(output.is_open())
    {
        output << aoc7p2(g);
        output.close();
    }
    return 0;
}
