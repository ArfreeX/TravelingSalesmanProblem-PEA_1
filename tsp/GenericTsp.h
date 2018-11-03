#pragma once
#ifndef TSP_H
#define TSP_H

#include <vector>
#include <limits.h>
#include <list>
#include <iostream>

namespace tsp
{

class GenericTsp
{
public:
    GenericTsp(std::vector<std::vector<int>> roadMap);

    int getDistanceBetween(unsigned source, unsigned destination);

    bool checkIfVisited(unsigned city);

    std::string resultToString();

    virtual void computeBestRoute() = 0;

    virtual ~GenericTsp() = 0;

protected:
    std::vector<std::vector<int>> roadMap;
    std::vector<std::vector<int>> bestRoute;
    std::vector<bool> visitedCities;
    int routeWeight = INT_MAX;
};

} // namespace tsp
#endif // TSP_H
