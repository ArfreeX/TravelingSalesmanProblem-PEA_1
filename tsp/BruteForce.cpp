#include "BruteForce.h"
#include <algorithm>

namespace tsp
{

BruteForce::BruteForce(std::vector<std::vector<int>> roadMap)
    : GenericTsp(roadMap)
{
    if(!roadMap.size())
    {
        return;
    }

    for(unsigned i = 1; i < roadMap.size(); i++)
    {
        cities.push_back(i);
    }

    bestRoute.resize(roadMap.size());
    bestRoute[0][0] = 0;
    bestRoute[0][1] = 0;
};

void BruteForce::computeBestRoute()
{
    if(roadMap.empty())
    {
        return;
    }

    std::vector<unsigned> tempCitiesOrder;
    unsigned long lastCity = cities.size() - 1;
    do
    {
        int temporaryRoadWeight = roadMap[0][cities[0]];
        for(unsigned i = 0; i < lastCity; i++)
        {
            temporaryRoadWeight += roadMap[cities[i]][cities[i+1]];
        }
        temporaryRoadWeight += roadMap[lastCity][0];


        if(temporaryRoadWeight < routeWeight)
        {
            routeWeight = temporaryRoadWeight;
            for(unsigned i = 1; i < roadMap.size(); i++)
            {
                bestRoute[i][0] = cities[i - 1];
                bestRoute[i][1] = roadMap[cities[i - 1]][cities[i]];
            }
        }
    }while(std::next_permutation(cities.begin(), cities.end()));
}

} // namespace tsp
