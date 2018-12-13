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
    GenericTsp(std::vector<std::vector<int>> providedRoadMap);

    int getDistanceBetween(unsigned source, unsigned destination);

    std::string resultToString();

    virtual void computeBestRoute() = 0;

    virtual ~GenericTsp() = 0;

    int minRouteWeight = INT_MAX;
protected:
    std::vector<std::vector<int>> roadMap;
    std::vector<std::vector<int>> bestRoute;

    const int STARTING_CITY = 0;
};

} // namespace tsp
#endif // TSP_H
