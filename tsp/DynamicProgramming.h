#pragma once
#ifndef DYNAMICPROGRAMMING_H
#define DYNAMICPROGRAMMING_H

#include <list>
#include "GenericTsp.h"

namespace tsp
{

class DynamicProgramming :
    public GenericTsp
{
public:
    DynamicProgramming(std::vector<std::vector<int>> roadMap);

    ~DynamicProgramming();

    void computeBestRoute();

private:
    void setup();

    std::list<unsigned> createSubsets(unsigned r);
    void createSubsets(unsigned set, unsigned at, unsigned r, unsigned n, std::list<unsigned> & subsets);

    bool checkIfElemInSubset(unsigned elem, unsigned subset);

    void findMinimalRouteWeight();

    std::vector<unsigned> createOrderOfVisits();

    void findOrderOfVisits(std::vector<unsigned> cities);

    std::vector<std::vector<unsigned>> memo;
    unsigned numbOfCities;
    const unsigned ALL_VISITED;
};

} // namespace tsp
#endif // DYNAMICPROGRAMMING_H
