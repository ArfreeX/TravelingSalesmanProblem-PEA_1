#include "TabuSearch.h"
#include "helpers/Timer.h"
#include <algorithm>
#include "helpers/RandomNumberGenerator.h"

namespace tsp
{

TabuSearch::TabuSearch(std::vector<std::vector<int>> roadMap, long long int timeLimit)
    : GenericTsp (roadMap),
      tabuList(roadMap.size()),
      timeLimit(timeLimit),
      numbOfCities(roadMap.size())
{
    setupFirstSolution();
}

TabuSearch::~TabuSearch()
{

}

void TabuSearch::computeBestRoute()
{
    helpers::Timer timer;
    timer.start();
    minRouteWeight = calculateDistance(processingSolution);
    currentBestSolution = processingSolution;
    std::vector<int> firstSolution = processingSolution;
    std::vector<int> previousSolution = processingSolution;
    int nothingChanged = 0;
    while(timer.elapsedSec() < timeLimit)
    {
        nothingChanged++;
        int index, index2, indexPenalty = 0, index2Penalty = 0;
        do {
            index = rand() % (currentBestSolution.size() - 2) + 1;
            index2 = rand() % (currentBestSolution.size() - 2) + 1;
        }while(index == index2);


        std::swap(processingSolution[index], processingSolution[index2]);

        int processingCost = calculateDistance(processingSolution);

        if(processingCost < minRouteWeight)
        {
            minRouteWeight = processingCost;
            currentBestSolution = processingSolution;
            indexPenalty = index;
            index2Penalty = index2;
            nothingChanged = 0;
        }

        if(nothingChanged % 2000 == 0)
        {
            processingSolution = invertSubsolution(processingSolution);
        }

        if(indexPenalty)
        {
            tabuList.penalize(indexPenalty, index2Penalty);
            tabuList.decrement();
        }

    }
    assignRoute(currentBestSolution);
}

unsigned TabuSearch::calculateDistance(std::vector<int> solution)
{
    unsigned cost = 0;
    for (int i = 0; i < solution.size() - 1; i++)
    {
        cost += roadMap[solution[i]][solution[i + 1]];
    }
    return cost;
}

void TabuSearch::setupFirstSolution()
{
    std::vector<bool> visitedCities(numbOfCities);
    struct {
        int city;
        int weight;
    } nextPotentialCity;

    for(int i = 0 ; i < numbOfCities; i++)
    {
        visitedCities[i] = false;
    }

    processingSolution.push_back(0);
    visitedCities[0] = true;
    int lastCity = 0;

    while(processingSolution.size() != numbOfCities){
        nextPotentialCity.weight = INT_MAX;
        for(int i = 0 ; i < numbOfCities; i++)
        {
            if(!visitedCities[i] && roadMap[lastCity][i] < nextPotentialCity.weight && lastCity != i)
            {
                nextPotentialCity.weight = roadMap[lastCity][i];
                nextPotentialCity.city = i;
            }
        }
        lastCity = nextPotentialCity.city;
        visitedCities[nextPotentialCity.city] = true;
        processingSolution.push_back(nextPotentialCity.city);
    }
    processingSolution.push_back(processingSolution[0]);
}

std::vector<int> TabuSearch::invertSubsolution(std::vector<int> solution)
{
    auto newSolution = solution;
    size_t first, second;
    std::random_device randomGenerator;
    std::uniform_int_distribution<int> firstDist(1, solution.size() - 2);
    std::uniform_int_distribution<int> secondDist(1, solution.size() - 3);

    first = firstDist(randomGenerator);
    second = secondDist(randomGenerator);
    if (first <= second)
    {
        ++second;
    }
    if (first < second)
        std::reverse(solution.begin() + first, solution.begin() + second);
    else
        std::reverse(solution.begin() + second, solution.begin() + first);

    return newSolution;
}

void TabuSearch::assignRoute(std::vector<int> bestSolution)
{
    for(unsigned i = 0; i < bestSolution.size(); i++)
    {
        bestRoute[i][0] = bestSolution[i];

        if(i)
        {
            bestRoute[i][1] = roadMap[bestSolution[i - 1]][bestSolution[i]];
        }
    }
}

} // namespace tsp
