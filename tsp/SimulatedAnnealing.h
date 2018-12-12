#pragma once
#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H

#include <list>
#include "GenericTsp.h"
#include "helpers/Timer.h"

namespace tsp
{

class SimulatedAnnealing :
    public GenericTsp
{
public:
    SimulatedAnnealing(std::vector<std::vector<int>> roadMap, long long int timeLimit);

    ~SimulatedAnnealing();

    void computeBestRoute();

private:
    int getTotalDistance(std::vector<int> actualOrder);
    std::vector<std::vector<unsigned>> memo;
    unsigned numbOfCities;
    long long int timeLimit;
};

} // namespace tsp
#endif // SIMULATEDANNEALING_H
