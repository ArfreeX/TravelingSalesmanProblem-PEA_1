#pragma once
#ifndef TABUSEARCH_H
#define TABUSEARCH_H

#include <list>
#include <queue>
#include "GenericTsp.h"
#include "helpers/RandomNumberGenerator.h"
#include "tsp/TabuList.h"
#include "tsp/SimulatedAnnealing.h"

namespace tsp
{

class TabuSearch :
    public GenericTsp
{
public:
    tsp::SimulatedAnnealing::NeighbourhoodMove tspNeighbourhoodStrategy;

    TabuSearch(std::vector<std::vector<int>> roadMap, long long int timeLimit,
               tsp::SimulatedAnnealing::NeighbourhoodMove tspNeighbourhoodStrategy);

    ~TabuSearch();

    void computeBestRoute();

private:
    unsigned calculateDistance(std::vector<int> solution);

    void setupFirstSolution();

    void assignRoute(std::vector<int>);

    std::vector<int> swapTwoCities(std::vector<int> solution);

    std::vector<int> randomlyInsertCity(std::vector<int> solution);

    std::vector<int> invertSubsolution(std::vector<int> solution);

    TabuList tabuList;
    std::vector<int> processingSolution;
    std::vector<int> currentBestSolution;
    int indexCity, indexCity2;
    unsigned numbOfCities;
    long long int timeLimit;
    int numberOfIterations;

    //int[] bestSolution; ->  std::vector<std::vector<int>> bestRoute;
    //int bestCost; -> int minRouteWeight = INT_MAX;
};

} // namespace tsp
#endif // TABUSEARCH_H
