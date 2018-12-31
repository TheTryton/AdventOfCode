#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>

using namespace std;

struct point
{
    int x, y, z, w;
};

int to_int(const string& s)
{
    stringstream ss(s);
    int r;
    ss >> r;
    return r;
}

int manhattan_dist(const point& a, const point& b)
{
    return abs(a.x - b.x) + abs(a.y - b.y) + abs(a.z - b.z) + abs(a.w - b.w);
}

std::vector<std::string> split(const std::string& s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

point parse_point(const string& s)
{
    point p;
    auto c = split(s, ',');
    p.x = to_int(c[0]);
    p.y = to_int(c[1]);
    p.z = to_int(c[2]);
    p.w = to_int(c[3]);
    return p;
}

vector<point> parse_input()
{
    ifstream file;
    file.open("AOC25_in.txt");
    vector<point> pts;
    if (file.is_open())
    {
        while (!file.eof())
        {
            string line;
            getline(file, line);
            if (!line.empty())
            {
                pts.push_back(parse_point(line));
            }
        }
        file.close();
    }
    return pts;
}

int main()
{
    auto input_pts = parse_input();
    vector<list<point>> constelations;
    for (auto& pt : input_pts)
    {
        vector<vector<list<point>>::iterator> constellation_candidates;
        for (auto b = constelations.begin(); b != constelations.end(); b++)
        {
            if (any_of(b->begin(), b->end(),
                [&pt](const point& p) {
                return manhattan_dist(pt, p) <= 3;
            })
                )
            {
                constellation_candidates.push_back(b);
            }
        }

        if (constellation_candidates.empty())
        {
            constelations.push_back({ pt });
        }
        else
        {
            auto& main_candidate = *constellation_candidates.front();
            constellation_candidates.erase(constellation_candidates.begin());
            for (auto& other_candidate : constellation_candidates)
            {
                main_candidate.insert(main_candidate.begin(), other_candidate->begin(), other_candidate->end());
            }
            main_candidate.push_back(pt);
            for(size_t i=0;i<constellation_candidates.size();i++)
            {
                constelations.erase(constellation_candidates[i]-i);
            }
        }
    }

    for (auto& c : constelations)
    {
        cout << c.size() << endl;
    }

    cout << constelations.size() << endl;
    return 0;
}
