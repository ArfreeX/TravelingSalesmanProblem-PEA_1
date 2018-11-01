#include "GenericTsp.h"

namespace tsp
{

GenericTsp::GenericTsp(std::vector<std::vector<int>> roadMap)
{
    this->roadMap = roadMap;

    bestRoute.resize(roadMap.size());
    for(auto & city : bestRoute)
    {
        city.resize(2);
    }
}

GenericTsp::~GenericTsp() {}

void GenericTsp::printResult()
{
    if(bestRoute.empty())
    {
        std::cout << "No routes found";
        return;
    }

    for(auto & city : bestRoute)
    {
        std::cout << "City: " << city[0]
            << "\tWeight: " << city[1] << std::endl;
    }
    std::cout << "Total weight: " << routeWeight
        << std::endl;
}

} // namespace tsp
