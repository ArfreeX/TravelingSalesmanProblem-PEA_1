#include "TabuSearch.h"
#include "helpers/Timer.h"
#include <algorithm>
#include "helpers/RandomNumberGenerator.h"


namespace tsp
{

TabuSearch::TabuSearch(std::vector<std::vector<int>> roadMap, long long int timeLimit,
                       tsp::SimulatedAnnealing::NeighbourhoodMove tspNeighbourhoodStrategy)
    : GenericTsp (roadMap),
      tabuList(roadMap.size()),
      timeLimit(timeLimit),
      numbOfCities(roadMap.size()),
      tspNeighbourhoodStrategy(tspNeighbourhoodStrategy)
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
    auto nextSolution = processingSolution;
    int nothingChanged = 0;
    int currentBestWeight = minRouteWeight;
    while(timer.elapsedSec() < timeLimit)
    {
        nothingChanged++;
        switch(tspNeighbourhoodStrategy)
        {
            case tsp::SimulatedAnnealing::NeighbourhoodMove::SWAP:
                nextSolution = swapTwoCities(processingSolution);
                break;
            case tsp::SimulatedAnnealing::NeighbourhoodMove::INSERT:
                nextSolution = randomlyInsertCity(processingSolution);
                break;
            case tsp::SimulatedAnnealing::NeighbourhoodMove::INVERT:
                nextSolution = invertSubsolution(processingSolution);
                break;
        }

        int currentBestWeight = calculateDistance(processingSolution);
        int nextSolCost = calculateDistance(nextSolution);

        if(!tabuList.isPenalized(indexCity, indexCity2))
        {
            processingSolution = nextSolution;
            tabuList.penalize(indexCity, indexCity2);
            if(nextSolCost < currentBestWeight)
            {
                currentBestWeight = nextSolCost;
                if(minRouteWeight > currentBestWeight)
                {
                    minRouteWeight = nextSolCost;
                    currentBestSolution = processingSolution;
                }
                nothingChanged = 0;
            }
        }

        tabuList.decrement();
        if(nothingChanged % 20000 == 0)
        {
            std::next_permutation(processingSolution.begin(), processingSolution.end());
            std::next_permutation(processingSolution.begin(), processingSolution.end());
            std::next_permutation(processingSolution.begin(), processingSolution.end());
            std::next_permutation(processingSolution.begin(), processingSolution.end());
            processingSolution = invertSubsolution(processingSolution);
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

std::vector<int> TabuSearch::swapTwoCities(std::vector<int> solution)
{
    auto newSolution = solution;
    size_t first, second;
    std::random_device randomGenerator;
    std::uniform_int_distribution<int> firstDist(1, solution.size() - 2);
    std::uniform_int_distribution<int> secondDist(1, solution.size() - 3);

    first = firstDist(randomGenerator);
    second = secondDist(randomGenerator);
    if (first < second)
    {
        ++second;
    }
    if (first == second )
    {
        ++second;
    }
    std::swap(newSolution[first], newSolution[second]);
    indexCity = first;
    indexCity2 = second;
    return newSolution;
}

std::vector<int> TabuSearch::randomlyInsertCity(std::vector<int> solution)
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
    auto element = *(solution.begin() + first);
    solution.erase(solution.begin() + first);
    solution.insert(solution.begin() + second, element);
    indexCity = first;
    indexCity2 = second;
    return newSolution;
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
    if (first < second)
    {
        ++second;
    }
    if (first == second)
    {
        ++second;
    }
    if (first < second)
        std::reverse(solution.begin() + first, solution.begin() + second);
    else
        std::reverse(solution.begin() + second, solution.begin() + first);
    indexCity = first;
    indexCity2 = second;
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
