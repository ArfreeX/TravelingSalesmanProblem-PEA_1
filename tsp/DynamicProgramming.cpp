#include "DynamicProgramming.h"
#include <algorithm>
namespace tsp
{

DynamicProgramming::DynamicProgramming(std::vector<std::vector<int>> roadMap)
    : GenericTsp(roadMap)
{
    N = roadMap.size();
    memo.resize(N);
    for(auto & line : memo)
    {
        line.resize(1 << N);
    }
};

DynamicProgramming::~DynamicProgramming()
{};

void DynamicProgramming::computeBestRoute()
{
    const int END_STATE = (1 << N) - 1;
    setup();

    for(int r = 3; r <= N; r++)
    {
        for(auto & subset : combinations(r))
        {
            if(notIn(0,subset)) continue;
            for(int next = 0; next < N; next++)
            {
                if(next == 0 || notIn(next, subset)) continue;
                int subsetWithoutNext = subset ^ (1 << next);
                int minDist = INT_MAX;
                for(int end = 0; end < N; end++)
                {
                    if(end == 0 || end == next || notIn(end, subset)) continue;
                    int newDistance = memo[end][subsetWithoutNext] + roadMap[end][next];
                    if(newDistance  < minDist)
                    {
                        minDist = newDistance;
                    }
                }
                memo[next][subset] = minDist;
            }
        }
    }

    for (int i = 1; i < N; i++)
    {
        int tourCost = memo[i][END_STATE] + roadMap[i][0];
        if(tourCost < minRouteWeight)
        {
            minRouteWeight = tourCost;
        }
    }
    std::vector<int> cities;
    int lastIndex = 0;
    int state = END_STATE;
    cities.emplace_back(0);

    for ( int i = 1; i < N; i++)
    {
        int index = -1;
        for( int j = 0 ; j < N; j++)
        {
            if ( j == 0 || notIn(j, state)) continue;
            if ( index == -1) index = j;
            int prevDist = memo[index][state] + roadMap[index][lastIndex];
            int newDist = memo[j][state] + roadMap[j][lastIndex];
            if ( newDist < prevDist)
            {
                index = j;
            }
        }
        cities.emplace_back(index);
        state = state ^ ( 1 << index);
        lastIndex = index;
    }

    cities.emplace_back(0);
    std::reverse(cities.begin(), cities.end());

    for(unsigned i = 0; i < cities.size(); i++)
    {
        bestRoute[i][0] = cities[i];

        if(i)
        {
            bestRoute[i][1] = roadMap[cities[i - 1]][cities[i]];
        }
        else
        {
            bestRoute[0][1] = 0;
        }
    }
    minRouteWeight = 0;
    for(auto & route : bestRoute)
    {
        minRouteWeight += route[1];
    }

}

bool DynamicProgramming::notIn(int elem, int subset)
{
  return ((1 << elem) & subset) == 0;
}

void DynamicProgramming::setup()
{
    for(int i = 1; i < N; i++)
    {
        memo[i][(1 << 0) | (1 << i)] = roadMap[0][i];
    }
}

std::list<int> DynamicProgramming::combinations(int r)
{
    std::list<int> subsets;
    combinations(0,0,r,N,subsets);
    return subsets;
}

void DynamicProgramming::combinations(int set, int at, int r, int n, std::list<int> subsets)
{
    int elementsLeftToPick = n - at;
    if (elementsLeftToPick < r) return;

    if ( r == 0)
    {
        subsets.push_back(set);
    }
    else
    {
        for(int i = at; i < n; i++)
        {
            set |= 1 << i;

            combinations(set, i + 1, r - 1, n, subsets);

            set &= ~(1 << i);
        }
    }
}

} // namespace tsp
