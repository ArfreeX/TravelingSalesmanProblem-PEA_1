#include "DynamicProgramming.h"
#include <algorithm>
namespace tsp
{

DynamicProgramming::DynamicProgramming(std::vector<std::vector<int>> roadMap)
    : GenericTsp(roadMap),
      ALL_VISITED((1 << roadMap.size()) - 1)
{
    if(roadMap.empty() || roadMap.size() > 25)
    {
        return;
    }

    numbOfCities = roadMap.size();
    memo.resize(numbOfCities);
    for(auto & line : memo)
    {
        line.resize(1 << numbOfCities);
        std::fill(line.begin(), line.end(), INT_MAX);
    }
};

DynamicProgramming::~DynamicProgramming()
{};

void DynamicProgramming::setup()
{
    for (unsigned i = 1; i < numbOfCities; i++)
    {
      memo[i][1 | (1 << i)] = roadMap[0][i];
    }
}
void DynamicProgramming::findMinimalRouteWeight()
{
    minRouteWeight = 0;
    for(auto & route : bestRoute)
    {
        minRouteWeight += route[1];
    }
}

void DynamicProgramming::findOrderOfVisits(std::vector<unsigned> cities)
{
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
}

std::vector<unsigned> DynamicProgramming::createOrderOfVisits()
{
    std::vector<unsigned> cities;
    unsigned lastCityIndex = 0;
    unsigned visited = ALL_VISITED;
    cities.emplace_back(0);
    for ( unsigned i = 1; i < numbOfCities; i++)
    {
        unsigned cityIndex = INT_MAX;
        for( unsigned j = 1 ; j < numbOfCities; j++)
        {
            if (checkIfElemInSubset(j, visited))
            {
                if ( cityIndex == INT_MAX)
                {
                    cityIndex = j;
                }

                int prevDist = memo[cityIndex][visited] + roadMap[cityIndex][lastCityIndex];
                int newDist = memo[j][visited] + roadMap[j][lastCityIndex];
                if ( newDist < prevDist)
                {
                    cityIndex = j;
                }
            }
        }
        cities.emplace_back(cityIndex);
        visited = visited ^ ( 1 << cityIndex);
        lastCityIndex = cityIndex;
    }
    cities.emplace_back(0);
    std::reverse(cities.begin(), cities.end());

    return cities;
}

void DynamicProgramming::computeBestRoute()
{
    if(roadMap.empty() || roadMap.size() > 25)
    {
        return;
    }

    setup();

    for(unsigned subsetSize = 3; subsetSize <= numbOfCities; subsetSize++)
    {
        for(auto & subset : createSubsets(subsetSize))
        {
            if(checkIfElemInSubset(0,subset))
            {
                for(unsigned nextNode = 1; nextNode < numbOfCities; nextNode++)
                {
                    if(checkIfElemInSubset(nextNode, subset))
                    {
                        unsigned subsetWithoutNextNode = subset ^ (1 << nextNode);

                        minRouteWeight = INT_MAX;
                        for(unsigned endNode = 1; endNode < numbOfCities; endNode++)
                        {
                            if(endNode != nextNode && checkIfElemInSubset(endNode, subset))
                            {
                                unsigned routeWeightThroughCurrentSubset = memo[endNode][subsetWithoutNextNode]
                                                                                + roadMap[endNode][nextNode];
                                if(routeWeightThroughCurrentSubset  < minRouteWeight)
                                {
                                    minRouteWeight = routeWeightThroughCurrentSubset;
                                }
                            }
                        }
                        memo[nextNode][subset] = minRouteWeight;
                    }
                }
            }
        }
    }

    auto cities = createOrderOfVisits();

    findOrderOfVisits(cities);

    findMinimalRouteWeight();
}

bool DynamicProgramming::checkIfElemInSubset(unsigned elem, unsigned subset)
{
  return ((1 << elem) & subset) != 0;
}

std::list<unsigned> DynamicProgramming::createSubsets(unsigned r)
{
    std::list<unsigned> subsets;
    createSubsets(0,0,r,numbOfCities,subsets);
    return subsets;
}

void DynamicProgramming::createSubsets(unsigned set, unsigned at, unsigned r, unsigned n, std::list<unsigned> & subsets)
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

            createSubsets(set, i + 1, r - 1, n, subsets);

            set &= ~(1 << i);
        }
    }
}

} // namespace tsp
