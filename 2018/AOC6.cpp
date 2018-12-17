#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

struct point
{
    int x,y;
};

int to_int(string a)
{
    stringstream ss(a);
    int v;
    ss >> v;
    return v;
}

point parse_point(string a)
{
    point p;
    auto comma = a.find(',');
    p.x = to_int(a.substr(0,comma));
    a = a.substr(comma+1);
    p.y = to_int(a);
    return p;
}

vector<point> load_input()
{
    vector<point> points;

    ifstream input;
    input.open("AOC6_in.txt");
    if(input.is_open())
    {
        while(!input.eof())
        {
            string line;
            getline(input, line);
            if(!line.empty())
            {
                points.push_back(parse_point(line));
            }
        }
        input.close();
    }

    return points;
}

int manhattan_distance(const point& a, const point& b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}

size_t largest_area(const vector<point>& pts)
{
    int x_min = std::numeric_limits<int>::max();
    int x_max = std::numeric_limits<int>::min();
    int y_min = std::numeric_limits<int>::max();
    int y_max = std::numeric_limits<int>::min();

    for(auto& pt : pts)
    {
        x_min = min(x_min, pt.x);
        x_max = max(x_max, pt.x);
        y_min = min(y_min, pt.y);
        y_max = max(y_max, pt.y);
    }

    auto x_size = x_max - x_min + 1;
    auto y_size = y_max - y_min + 1;

    vector<vector<size_t>> point_map(x_size);
    for(auto& col : point_map)
    {
        col = vector<size_t>(y_size);
    }

    for(int x = x_min; x <= x_max; x++)
    {
        for(int y = y_min; y <= y_max; y++)
        {
            point mp;
            mp.x = x;
            mp.y = y;
            int min_dist = std::numeric_limits<int>::max();
            int index;
            int min_dist_count = 0;
            for(size_t i=0;i<pts.size();i++)
            {
                auto& pt = pts[i];
                int dist = manhattan_distance(pt, mp);
                if(dist < min_dist)
                {
                    min_dist = dist;
                    min_dist_count = 1;
                    index = i;
                }
                else if(dist == min_dist)
                {
                    min_dist_count++;
                }
            }
            if(min_dist_count==1)
            {
                point_map[x - x_min][y - y_min]=index;
                //cout << index << ' ';
            }
            else
            {
                point_map[x - x_min][y - y_min]=-1;
                //cout << '.' << ' ';
            }

        }
        //cout << endl;
    }

    vector<bool> pts_inf(pts.size(), false);
    vector<size_t> pts_area(pts.size(), 0);

    for(int x=0; x<x_size; x++)
    {
        for(int y=0; y<y_size; y++)
        {
            if(x == 0 || x == x_size - 1 ||
               y == 0 || y == y_size - 1)
            {
                if(point_map[x][y]!=-1)
                {
                    pts_inf[point_map[x][y]] = true;
                }
            }

            if(point_map[x][y]!=-1)
            {
                pts_area[point_map[x][y]]++;
            }
        }
    }

    size_t max_area = 0;

    for(size_t i=0;i<pts.size();i++)
    {
        if(!pts_inf[i])
        {
            max_area = max(max_area, pts_area[i]);
        }
    }

    return max_area;
}

size_t safe_region_size(const vector<point>& pts)
{
    int x_min = std::numeric_limits<int>::max();
    int x_max = std::numeric_limits<int>::min();
    int y_min = std::numeric_limits<int>::max();
    int y_max = std::numeric_limits<int>::min();

    for(auto& pt : pts)
    {
        x_min = min(x_min, pt.x);
        x_max = max(x_max, pt.x);
        y_min = min(y_min, pt.y);
        y_max = max(y_max, pt.y);
    }

    x_min-=5500;
    x_max+=5500;
    y_min-=5500;
    y_max+=5500;

    size_t safe_area = 0;

    for(int x = x_min; x <= x_max; x++)
    {
        for(int y = y_min; y <= y_max; y++)
        {
            point mp;
            mp.x = x;
            mp.y = y;
            int sum_dists = 0;
            for(size_t i=0;i<pts.size();i++)
            {
                auto& pt = pts[i];
                sum_dists += manhattan_distance(pt, mp);
            }
            if(sum_dists<10000)
            {
                safe_area++;
            }
        }
    }

    return safe_area;
}

int main()
{
    auto input = load_input();
    ofstream output;
    //output.open("AOC6_out.txt");
    cout << largest_area(input) << endl;
    cout << safe_region_size(input) << endl;
    /*if(output.is_open())
    {
        cout << aocp2(input) << endl;
        output << aocp1(input);
        output.close();
    }
*/

    return 0;
}
