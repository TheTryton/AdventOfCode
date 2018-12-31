#include <iostream>
#include <list>
#include <array>
#include <algorithm>

using namespace std;

void printv(const list<int>& marbles)
{
    auto cpy = marbles;
    reverse(cpy.begin(), cpy.end());
    for (auto& e : cpy)
    {
        cout << e << ", ";
    }
    cout << endl;
}

int main()
{
    constexpr int players_count = 468;
    constexpr int last_marble_value = 7101000;
    array<long long int, players_count> players_scores;
    fill(players_scores.begin(), players_scores.end(), 0);

    list<int> marbles;

    marbles.push_back(0);
    //printv(marbles);

    int marble = 1;
    int current_player = 0;
    list<int>::iterator current_marble_index = marbles.begin();
    while (marble <= last_marble_value)
    {
        if (marble % 23 == 0)
        {
            players_scores[current_player] += marble;
            for(int i=0;i<7;i++)
            {
                current_marble_index++;

                if(current_marble_index == marbles.end())
                {
                    current_marble_index = marbles.begin();
                }
            }
            players_scores[current_player] += *current_marble_index;
            current_marble_index = marbles.erase(current_marble_index);
            current_marble_index--;
        }
        else
        {
            if(current_marble_index == marbles.begin())
            {
                current_marble_index = marbles.end();
                current_marble_index--;
            }
            else
            {
                current_marble_index--;
            }
            current_marble_index=marbles.insert(current_marble_index, marble);
        }

        //cout << "[" << current_player + 1 << "] ";
        //printv(marbles);

        marble++;
        current_player = (current_player + 1) % players_count;
    }

    long long int max_score = *max_element(players_scores.begin(), players_scores.end());
    cout << max_score << endl;
    return 0;
}
