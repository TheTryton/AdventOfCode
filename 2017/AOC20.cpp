#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <thread>
#include <mutex>
#include <algorithm>

using namespace std;

template<class T>
struct Vector
{
    T x,y,z;
    T l_x,l_y,l_z;

    Vector(T x, T y, T z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector()
    {
        x=T();
        y=T();
        z=T();
    }

    double length()
    {
        return abs(x)+abs(y)+abs(z);
    }
};

typedef Vector<long long> VI;
typedef Vector<VI> PT;

int fromString(string val)
{
    stringstream ss(val);
    int out = 0;
    ss >> out;
    return out;
}

vector<PT> parseInput(vector<string> input)
{
    vector<PT> particles;
    for(string line : input)
    {
        PT particle;

        VI pos;
        line = line.substr(line.find('<')+1);
        pos.x = fromString(line);
        line = line.substr(line.find(',')+1);
        pos.y = fromString(line);
        line = line.substr(line.find(',')+1);
        pos.z = fromString(line);

        particle.x = pos;

        VI vel;
        line = line.substr(line.find('<')+1);
        vel.x = fromString(line);
        line = line.substr(line.find(',')+1);
        vel.y = fromString(line);
        line = line.substr(line.find(',')+1);
        vel.z = fromString(line);

        particle.y = vel;

        VI acc;
        line = line.substr(line.find('<')+1);
        acc.x = fromString(line);
        line = line.substr(line.find(',')+1);
        acc.y = fromString(line);
        line = line.substr(line.find(',')+1);
        acc.z = fromString(line);

        particle.z = acc;

        particles.push_back(particle);
    }

    return particles;
}

size_t firstPart(vector<PT> particles)
{
    size_t COUNT = 0;

    for(size_t j=0;j<particles.size();j++)
    {
        COUNT = max((size_t)abs(particles[j].x.x),COUNT);
        COUNT = max((size_t)abs(particles[j].x.y),COUNT);
        COUNT = max((size_t)abs(particles[j].x.z),COUNT);
    }

    COUNT*=2;

    int closestIndex = 0;

    for(int c=0;c<COUNT;c++)
    {
        closestIndex = 0;

        for(size_t j=0;j<particles.size();j++)
        {
            if(particles[j].x.length()<=particles[closestIndex].x.length())
            {
                closestIndex = j;
            }

            particles[j].y.x += particles[j].z.x;
            particles[j].y.y += particles[j].z.y;
            particles[j].y.z += particles[j].z.z;

            particles[j].x.x += particles[j].y.x;
            particles[j].x.y += particles[j].y.y;
            particles[j].x.z += particles[j].y.z;
        }
    }

    return closestIndex;
}

size_t secondPart(vector<PT> particles)
{
    size_t COUNT = 0;

    for(size_t j=0;j<particles.size();j++)
    {
        COUNT = max((size_t)abs(particles[j].x.x),COUNT);
        COUNT = max((size_t)abs(particles[j].x.y),COUNT);
        COUNT = max((size_t)abs(particles[j].x.z),COUNT);
    }

    COUNT;

    for(int c=0;c<COUNT;c++)
    {
        vector<size_t> collidingParts;
        for(size_t j=0;j<particles.size();j++)
        {
            for(size_t i=0;i<particles.size();i++)
            {
                if(i!=j)
                {
                    if(particles[j].x.x==particles[i].x.x&&
                       particles[j].x.y==particles[i].x.y&&
                       particles[j].x.z==particles[i].x.z)
                    {
                        collidingParts.push_back(j);
                        break;
                    }
                }
            }
        }

        sort(collidingParts.begin(),collidingParts.end(),[](size_t& a,size_t& b){
            return a>b;
        });

        for(size_t& a : collidingParts)
        {
            particles.erase(particles.begin()+a);
        }

        for(size_t j=0;j<particles.size();j++)
        {
            particles[j].y.x += particles[j].z.x;
            particles[j].y.y += particles[j].z.y;
            particles[j].y.z += particles[j].z.z;

            particles[j].x.x += particles[j].y.x;
            particles[j].x.y += particles[j].y.y;
            particles[j].x.z += particles[j].y.z;
        }

    }

    return particles.size();
}

int main()
{
    vector<string> input;

    string fileName;
    cout << "Paste input file name:" << endl;
    getline(cin,fileName);

    ifstream inputFile(fileName);

    string line = "";
    do
    {
        line = "";
        getline(inputFile, line);
        if (line != "")
            input.push_back(line);
    } while (line != "");

    vector<PT> particles = parseInput(input);

    cout << "First part: " << firstPart(particles) << endl;
    cout << "Second part: " << secondPart(particles) << endl;
}
