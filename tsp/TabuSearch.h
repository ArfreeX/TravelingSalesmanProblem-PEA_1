#pragma once
#ifndef TABUSEARCH_H
#define TABUSEARCH_H

#include <list>
#include <queue>
#include "GenericTsp.h"
#include "helpers/RandomNumberGenerator.h"
#include "tsp/TabuList.h"

namespace tsp
{

class TabuSearch :
    public GenericTsp
{
public:
    TabuSearch(std::vector<std::vector<int>> roadMap, long long int timeLimit);

    ~TabuSearch();

    void computeBestRoute();

private:
    unsigned calculateDistance(std::vector<int> solution);

    void setupFirstSolution();

    void assignRoute(std::vector<int>);

    std::vector<int> invertSubsolution(std::vector<int> solution);

    std::vector<int> swapCities(std::vector<int> currentPath,int city1,int city2);

    TabuList tabuList;
    std::vector<int> processingSolution;
    std::vector<int> currentBestSolution;

    unsigned numbOfCities;
    long long int timeLimit;
    int numberOfIterations;

    //int[] bestSolution; ->  std::vector<std::vector<int>> bestRoute;
    //int bestCost; -> int minRouteWeight = INT_MAX;
};

} // namespace tsp
#endif // TABUSEARCH_H
