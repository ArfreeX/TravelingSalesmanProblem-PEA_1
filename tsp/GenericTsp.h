#pragma oncea
#ifndef TSP_H
#define TSP_H

#include <vector>
#include <list>
#include <iostream>

namespace tsp
{

class GenericTsp
{
public:
    GenericTsp(std::vector<std::vector<int>> roadMap);

    void printResult();

    virtual void computeBestRoute() = 0;
    virtual ~GenericTsp() = 0;

protected:
    std::vector<std::vector<int>> roadMap;
    std::vector<std::vector<int>> bestRoute;
    int routeWeight = 0;
};

} // namespace tsp
#endif // TSP_H
