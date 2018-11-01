#pragma once
#ifndef TSPBRUTEFORCE_H
#define TSPBRUTEFORCE_H

#include "GenericTsp.h"

namespace tsp
{

class BruteForce :
        public GenericTsp
{
public:
    BruteForce(std::vector<std::vector<int>> roadMap);

    void computeBestRoute();
};

} // namespace tsp
#endif // TSPBRUTEFORCE_H
