#include "GenericTsp.h"

namespace tsp
{

GenericTsp::GenericTsp(std::vector<std::vector<int>> providedRoadMap)
    : roadMap(providedRoadMap)
{
    if(!roadMap.size())
    {
        return;
    }

    bestRoute.resize(roadMap.size() + 1);
    for(auto & city : bestRoute)
    {
        city.resize(2);
    }
    bestRoute[0][0] = 0;
    bestRoute[0][1] = 0;
}

GenericTsp::~GenericTsp() {}

int GenericTsp::getDistanceBetween(unsigned source, unsigned destination)
{
    return roadMap[source][destination];
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

    return resultString += "\nNumber of cities: " + std::to_string(bestRoute.size() - 1)
        + "\nTotal weight: " + std::to_string(minRouteWeight) + "\n";
}

} // namespace tsp
