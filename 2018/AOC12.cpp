#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
    string state = "..#...####.##..####..#.##....##...###.##.#..######..#..#..###..##.#.###.#####.##.#.#.#.##....#..#..#....";
    map<string, char> rules =
    {
        {"...##",'.'},
        {"...#.",'#'},
        {"....#",'.'},
        {"###.#",'#'},
        {".....",'.'},
        {"..#..",'#'},
        {"#.#.#",'.'},
        {"#..#.",'.'},
        {"#...#",'.'},
        {"##...",'.'},
        {".#.#.",'#'},
        {".#..#",'.'},
        {".###.",'.'},
        {"#..##",'#'},
        {"..#.#",'#'},
        {".####",'#'},
        {"##..#",'#'},
        {"##.#.",'#'},
        {".#...",'#'},
        {"#.#..",'.'},
        {"#####",'.'},
        {"###..",'#'},
        {".##.#",'.'},
        {"#.##.",'.'},
        {"..###",'.'},
        {".#.##",'#'},
        {"..##.",'#'},
        {"#.###",'.'},
        {".##..",'#'},
        {"##.##",'.'},
        {"#....",'.'},
        {"####.",'#'},
    };

    for(int i=0;i<20;i++)
    {
        string new_gen;
        new_gen.resize(state.size());

        new_gen[0]='.';
        new_gen[1]='.';
        new_gen[new_gen.size()-2]='.';
        new_gen[new_gen.size()-1]='.';

        for(size_t i=2;i<state.size()-2;i++)
        {
            auto state_near = state.substr(i-2,5);
            if(rules.find(state_near)!=rules.end())
            {
                new_gen[i] = rules[state_near];
            }
            else
            {
                new_gen[i]='.';
            }
        }
        state = new_gen;
    }

    cout << state << endl;
    size_t sum_i = 0;
    for(size_t i=2;i<state.size()-2;i++)
    {
        if(state[i] == '#')
        {
            sum_i+=i;
        }
    }
    cout << sum_i << endl;
    return 0;
}
