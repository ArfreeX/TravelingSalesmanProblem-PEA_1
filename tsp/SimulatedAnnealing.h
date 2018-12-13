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
    unsigned calculateDistance(std::vector<int> solution);

    double calculateDelta(std::vector<int> currentSolution, std::vector<int> nextSolution);

    std::vector<int> invertSubsolution(std::vector<int> solution);

    void setupFirstSolution(std::vector<int>& firstSolution);

    void assignRoute(std::vector<int>);

    std::vector<int> swapTwoCities(std::vector<int> solution);

    enum NeighbourhoodMove: uint8_t
    {
        INSERT,
        SWAP,
        INVERT
    };
    unsigned numbOfCities;
    long long int timeLimit;
};

} // namespace tsp
#endif // SIMULATEDANNEALING_H
