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
};

void BruteForce::computeBestRoute()
{
    if(roadMap.empty())
    {
        return;
    }
    std::cout << "DUPA";
    std::vector<unsigned> tempOrderOfCities;
    unsigned long lastCity = cities.size() - 1;
    do
    {
        int temporaryRoadWeight = roadMap[0][cities[0]];

        for(unsigned i = 0; i < lastCity; i++)
        {
            temporaryRoadWeight += roadMap[cities[i]][cities[i+1]];
        }
        temporaryRoadWeight += roadMap[lastCity][0];


        if(temporaryRoadWeight < minRouteWeight)
        {
            minRouteWeight = temporaryRoadWeight;
            tempOrderOfCities = cities;
        }
    }while(std::next_permutation(cities.begin(), cities.end()));

    cities = tempOrderOfCities;
    cities.emplace_back(0);

    for(unsigned i = 0; i < cities.size(); i++)
    {
        bestRoute[i + 1][0] = cities[i];

        if(i)
        {
            bestRoute[i + 1][1] = roadMap[cities[i - 1]][cities[i]];
        }
        else
        {
            bestRoute[1][1] = roadMap[0][cities[0]];
        }
    }
}

} // namespace tsp
