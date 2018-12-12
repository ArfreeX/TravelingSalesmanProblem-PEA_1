#pragma once
#ifndef TABUSEARCH_H
#define TABUSEARCH_H

#include <list>
#include <queue>
#include "GenericTsp.h"
#include "helpers/Timer.h"
#include "helpers/RandomNumberGenerator.h"
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
    void tabuMove(int city1, int city2);

    void decrementTabu();

    unsigned calculateDistance(std::vector<int> solution);

    void setupBestSolution();

    void setupCurrentSolution();

    std::vector<int> swap(int i, int k, std::vector<int> solution);

    void assignRoute(std::vector<int>);

    void resetTabuList();

    std::vector<std::vector<int>> tabuList;
    std::vector<int> currSolution;
    std::vector<int> bestSolution;

    unsigned numbOfCities;
    long long int timeLimit;

    int numberOfIterations;

    //int[] bestSolution; ->  std::vector<std::vector<int>> bestRoute;
    //int bestCost; -> int minRouteWeight = INT_MAX;
};

} // namespace tsp
#endif // TABUSEARCH_H
