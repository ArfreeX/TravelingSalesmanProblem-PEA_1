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
    std::list<int> combinations(int r);

private:
    void setup();
    void combinations(int set, int at, int r, int n, std::list<int> subsets);
    bool notIn(int elem, int subset);
    std::vector<std::vector<int>> memo;
    unsigned long N;
};

} // namespace tsp
#endif // DYNAMICPROGRAMMING_H
