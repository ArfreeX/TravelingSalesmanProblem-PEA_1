#pragma once
#ifndef DYNAMICPROGRAMMING_H
#define DYNAMICPROGRAMMING_H

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
};

} // namespace tsp
#endif // DYNAMICPROGRAMMING_H
