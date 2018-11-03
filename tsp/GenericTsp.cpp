#include "GenericTsp.h"

namespace tsp
{

GenericTsp::GenericTsp(std::vector<std::vector<int>> roadMap)
{
    this->roadMap = roadMap;

    if(!roadMap.size())
    {
        return;
    }

    bestRoute.resize(roadMap.size());
    for(auto & city : bestRoute)
    {
        city.resize(2);
    }

    visitedCities.resize(roadMap.size());
    std::fill(visitedCities.begin(), visitedCities.end(), false);

    visitedCities[0] = true;
}

GenericTsp::~GenericTsp() {}

int GenericTsp::getDistanceBetween(unsigned source, unsigned destination)
{
    return roadMap[source][destination];
}

bool GenericTsp::checkIfVisited(unsigned city)
{
    return visitedCities[city];
}

std::string GenericTsp::resultToString()
{
    if(bestRoute.empty())
    {
        return "No routes found";
    }

    std::string resultString("");

    for(auto & city : bestRoute)
    {
        resultString += "City: " + std::to_string(city[0])
            + ",\tweight: " + std::to_string(city[1]) + "\n";
    }

    return resultString += "\nNumber of cities: " + std::to_string(bestRoute.size())
        + "\nTotal weight: " + std::to_string(routeWeight) + "\n";
}

} // namespace tsp
