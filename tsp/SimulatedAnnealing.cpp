#include "SimulatedAnnealing.h"
#include <math.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <queue>
#include <random>

namespace tsp
{

SimulatedAnnealing::SimulatedAnnealing(std::vector<std::vector<int>> roadMap, long long int timeLimit,
                                       tsp::SimulatedAnnealing::NeighbourhoodMove tspNeighbourhoodStrategy)
    : GenericTsp (roadMap),
      timeLimit(timeLimit),
      numbOfCities(roadMap.size()),
      tspNeighbourhoodStrategy(tspNeighbourhoodStrategy)
{

}

SimulatedAnnealing::~SimulatedAnnealing()
{

}

void SimulatedAnnealing::computeBestRoute()
{
    unsigned int iterations = 0;
    bool changedSubsolution = false;
    std::random_device randomGenerator;
    std::mt19937 gen(randomGenerator());
    std::uniform_real_distribution<> distribution(0.0, 1.0);
    setupFirstSolution();
    double delta;
    double cooling = 0.9997;
    double temperature = 20;
    const double STOP_TEMP = 1.00E-05;
    size_t notChanged = 0;
    std::vector<int> bestSolution(processingSolution);
    std::vector<int> nextSolution;

    auto move = NeighbourhoodMove::SWAP;
    helpers::Timer timer;
    timer.start();
    while (temperature > STOP_TEMP && timer.elapsedSec() < timeLimit)
    {
        notChanged++;

        switch(tspNeighbourhoodStrategy)
        {
            case NeighbourhoodMove::SWAP:
                nextSolution = swapTwoCities(processingSolution);
                break;
            case NeighbourhoodMove::INSERT:
                nextSolution = randomlyInsertCity(processingSolution);
                break;
            case NeighbourhoodMove::INVERT:
                nextSolution = invertSubsolution(processingSolution);
                break;
        }


        delta = calculateDelta(processingSolution, nextSolution);
        if (delta <= 0 || (distribution(gen) < std::exp(-delta / temperature)))
        {
            processingSolution = nextSolution;
        }
        if (calculateDistance(bestSolution) > calculateDistance(processingSolution))
        {
            bestSolution = processingSolution;
            notChanged = 0;
        }
        ++iterations;
        if (iterations % 1000 == 0)
        {
            temperature *= cooling;
        }
        if (notChanged % 20000 == 0)
        {
            nextSolution = invertSubsolution(processingSolution);
            changedSubsolution = true;
        }
    }
    minRouteWeight = 0;
    for (size_t i = 0; i < bestSolution.size() - 1; i++)
    {
        minRouteWeight += roadMap[bestSolution[i]][bestSolution[i + 1]];
    }
    assignRoute(bestSolution);
}

unsigned SimulatedAnnealing::calculateDistance(std::vector<int> solution)
{
    unsigned cost = 0;
    for (int i = 0; i < solution.size() - 1; i++)
    {
        cost += roadMap[solution[i]][solution[i + 1]];
    }
    return cost;
}

double SimulatedAnnealing::calculateDelta(std::vector<int> processingSolution, std::vector<int> nextSolution)
{
    double currentCost = 0;
    double nextCost = 0;
    for (size_t i = 0; i < processingSolution.size() - 1; i++)
    {
        currentCost += roadMap[processingSolution[i]][processingSolution[i + 1]];
        nextCost += roadMap[nextSolution[i]][nextSolution[i + 1]];
    }
    return (nextCost - currentCost) / currentCost;
}

std::vector<int> SimulatedAnnealing::swapTwoCities(std::vector<int> solution)
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
    return newSolution;
}

std::vector<int> SimulatedAnnealing::randomlyInsertCity(std::vector<int> solution)
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

    return newSolution;
}

std::vector<int> SimulatedAnnealing::invertSubsolution(std::vector<int> solution)
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

    return newSolution;
}

void SimulatedAnnealing::setupFirstSolution()
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

void SimulatedAnnealing::assignRoute(std::vector<int> bestSolution)
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
