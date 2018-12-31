#include <iostream>
#include <vector>

using namespace std;

long long int calculate_power(long long int x, long long int y, long long int serial)
{
    long long int rack_id = x + 10;
    long long int power_level = rack_id * y;
    power_level += serial;
    power_level *= rack_id;
    power_level = (power_level/100)%10;
    power_level -= 5;
    return power_level;
}

long long int sum_power(const vector<vector<long long int>>& power_levels, int x, int y)
{
    long long int sum = 0;
    for(int xp=0;xp<3;xp++)
    {
        for(int yp=0;yp<3;yp++)
        {
            sum += power_levels[x+xp][y+yp];
        }
    }
    return sum;
}

long long int sum_partial(const vector<vector<long long int>>& power_p_sums, int x, int y, int s)
{
    long long int sum = power_p_sums[x+s-1][y+s-1];
    if(x>0)
    {
        sum -= power_p_sums[x-1][y+s-1];
    }
    if(y>0)
    {
        sum -= power_p_sums[x+s-1][y-1];
    }
    if(x>0&&y>0)
    {
        sum += power_p_sums[x-1][y-1];
    }
    return sum;
}

int main()
{
    constexpr long long int serial = 4842;

    vector<vector<long long int>> fuel_cells(300);
    for(long long int x=0;x<fuel_cells.size();x++)
    {
        fuel_cells[x] = vector<long long int>(300);
        for(long long int y=0;y<fuel_cells[x].size();y++)
        {
            fuel_cells[x][y] = calculate_power(x+1, y+1, serial);
        }
    }

    //PART 1

    long long int max_power = 0;
    long long int mx = 1;
    long long int my = 1;

    for(long long int x=0;x<fuel_cells.size() - 2;x++)
    {
        for(long long int y=0;y<fuel_cells[x].size() - 2;y++)
        {
            auto pow = sum_power(fuel_cells,x,y);
            if(pow > max_power)
            {
                max_power = pow;
                mx = x+1;
                my = y+1;
            }
        }
    }

    cout << "p1" << endl;
    cout << max_power << endl;
    cout << mx << ", " << my << endl;

    vector<vector<long long int>> fuel_cells_partial_sums(300);
    for(long long int x=0;x<fuel_cells_partial_sums.size();x++)
    {
        fuel_cells_partial_sums[x] = vector<long long int>(300);
        for(long long int y=0;y<fuel_cells_partial_sums[x].size();y++)
        {
            int partial_sum = fuel_cells[x][y];
            if(x>0)
            {
                partial_sum += fuel_cells_partial_sums[x-1][y];
            }
            if(y>0)
            {
                partial_sum += fuel_cells_partial_sums[x][y-1];
            }
            if(x>0&&y>0)
            {
                partial_sum -= fuel_cells_partial_sums[x-1][y-1];
            }
            fuel_cells_partial_sums[x][y] = partial_sum;
        }
    }

    //PART 2

    max_power = 0;
    mx = 1;
    my = 1;
    int ms = 0;

    for(int s=1;s<=300;s++)
    {
        for(long long int x=0;x<fuel_cells_partial_sums.size() - s + 1;x++)
        {
            for(long long int y=0;y<fuel_cells_partial_sums[x].size() - s + 1;y++)
            {
                auto sum = sum_partial(fuel_cells_partial_sums,x,y,s);
                if(sum > max_power)
                {
                    max_power = sum;
                    mx = x+1;
                    my = y+1;
                    ms = s;
                }
            }
        }
    }

    cout << "p2" << endl;
    cout << max_power << endl;
    cout << mx << ", " << my << ", " << ms << endl;

    return 0;
}
