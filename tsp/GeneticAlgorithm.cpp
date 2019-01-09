#include "GeneticAlgorithm.h"
#include <math.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <queue>
#include <random>

namespace tsp
{

GeneticAlgorithm::GeneticAlgorithm(std::vector<std::vector<int>> roadMap, long long int timeLimit,
                                    tsp::GeneticAlgorithm::MutatingStrategy tspMutatingStrategy,
                                   tsp::GeneticAlgorithm::CrossingStrategy tspCrossingStrategy,
                                   int population, int crossingFactor, int mutationFactor)
    : GenericTsp (roadMap),
      timeLimit(timeLimit),
      numbOfCities(roadMap.size()),
      tspMutatingStrategy(tspMutatingStrategy),
      tspCrossingStrategy(tspCrossingStrategy),
      populationSize(population),
      crossingFactor(crossingFactor / 1000.0),
      mutationFactor(mutationFactor / 1000.0)
{
    srand(666);
    createRandomPopulation();
    fitness.resize(populationSize);
}

GeneticAlgorithm::~GeneticAlgorithm()
{

}


void GeneticAlgorithm::createRandomPopulation()
{
    for(int i = 0 ; i < populationSize; i++)
    {
        std::vector<int> tempVector;
        for(int j = 0; j < roadMap.size(); j++)
        {
            tempVector.push_back(j);
        }
        tempVector.push_back(0);
        population.push_back(swapTwoCities(tempVector, roadMap.size() * 5));
    }
}


void GeneticAlgorithm::computeBestRoute()
{
    std::vector<int> bestSolution;
//    std::cout<<"\nNOWA POPULACJA" <<"\n";
//    printPopulation(population);
    //std::cout<<"\nNOWA POPULACJA" <<"\n";
    //printPopulation(population);
    helpers::Timer timer;
    timer.start();

    while(timer.elapsedSec() < timeLimit)
    {
        for(int i = 0 ; i < population.size(); i++)
        {
            auto distance = calculateDistance(population[i]);
            if(distance < minRouteWeight)
            {
                minRouteWeight = distance;
                bestSolution = population[i];
            }
            fitness[i] = 1.0 / (double)(distance + 1);
        }
        normalizeFitness();
        population = nextGeneration(population);
    }
    assignRoute(bestSolution);
}


void GeneticAlgorithm::normalizeFitness()
{
    double sum = 0;
    for(int i = 0 ; i < fitness.size(); i++)
    {
        sum += fitness[i];
    }

    for(int i = 0 ; i < fitness.size(); i++)
    {
        fitness[i] = fitness[i] / sum;
    }
}


std::vector<std::vector<int>> GeneticAlgorithm::nextGeneration(std::vector<std::vector<int>> &population)
{
    std::vector<std::vector<int>> newPopulation(population.size());
    for(int i = 0 ; i < population.size(); i++)
    {
        auto processingSubsetA = pickOne();
        auto processingSubsetB = pickOne();
        auto processingSubset = crossover(processingSubsetA, processingSubsetB);
        processingSubset = mutate(processingSubset);
        newPopulation[i] = processingSubset;
    }

    return newPopulation;
}


std::vector<int> GeneticAlgorithm::mutate(std::vector<int> order)
{
    float probability;

    for(int i = 0; i < order.size(); i++)
    {
        probability = float(rand()) / RAND_MAX;
        if(probability < mutationFactor)
        {
            if(tspMutatingStrategy == MutatingStrategy::SWAP)
            {
                order = swapTwoCities(order);
            }
            else if(tspMutatingStrategy == MutatingStrategy::INVERT)
            {
                order = invertSubsolution(order);
            }
            else
            {
                std::cout <<"\nError, cannot mutate\n";
                return order;
            }
        }
    }
    return order;
}


std::vector<int> GeneticAlgorithm::crossover(std::vector<int> processingOrderA, std::vector<int> processingOrderB)
{
    float probability = float(rand()) / RAND_MAX;
    if(probability > crossingFactor)
    {
        return processingOrderA;
    }

    if(tspCrossingStrategy == CrossingStrategy::SUBSET)
    {
        return crossWithSubset(processingOrderA, processingOrderB);
    }
    else
    {
        return crossCoinFlip(processingOrderA, processingOrderB);
    }
}


std::vector<int> GeneticAlgorithm::crossWithSubset(std::vector<int> processingOrderA, std::vector<int> processingOrderB)
{
    std::random_device randomGenerator;
    std::uniform_int_distribution<int> firstDist(1, processingOrderA.size() - 2);
    int startId = firstDist(randomGenerator);
    std::uniform_int_distribution<int> secondDist(startId + 1, processingOrderA.size() - 1);
    int endId = secondDist(randomGenerator);

    std::vector<int> order(&processingOrderA[startId], &processingOrderA[endId]);
    int leftSize = processingOrderA.size() - order.size();

    order.insert(order.begin(), 0);
    for(int i = 1; i < processingOrderB.size(); i++)
    {
        int  city = processingOrderB[i];
        if(std::find(order.begin(), order.end(), city) == order.end())
        {
            order.push_back(city);
        }
    }
    order.push_back(0);

    if(order.size() > processingOrderA.size())
    {
        std::cout<< order.size() << " " << processingOrderA.size() <<"\n";
        std::cout<<"\nCrossing error!";
    }

    return order;
}


std::vector<int> GeneticAlgorithm::crossCoinFlip(std::vector<int> processingOrderA, std::vector<int> processingOrderB)
{
    std::vector<int> order;
    std::random_device randomGenerator;
    std::uniform_int_distribution<int> coinFlip(0, 1);

    while(order.size() < processingOrderA.size() - 1)
    {
        for(int i = 0; i < processingOrderA.size(); i++)
        {
            int cityA = processingOrderA[i];
            int cityB = processingOrderB[i];
            if(coinFlip(randomGenerator))
            {
                if(std::find(order.begin(), order.end(), cityA) == order.end())
                {
                    order.push_back(cityA);
                }
                else if(std::find(order.begin(), order.end(), cityB) == order.end())
                {
                    order.push_back(cityB);
                }
            }
            else
            {
                if(std::find(order.begin(), order.end(), cityB) == order.end())
                {
                    order.push_back(cityB);
                }
                else if(std::find(order.begin(), order.end(), cityA) == order.end())
                {
                    order.push_back(cityA);
                }
            }
        }
    }
    order.push_back(0);
    return order;
}


std::vector<int> GeneticAlgorithm::pickOne()
{
    int index = 0;
    bool loopDone = false;
    float probability = float(rand()) / RAND_MAX;

    while(probability > 0 && index < fitness.size())
    {
        probability -= fitness[index];
        index++;
        loopDone = true;
    }
    index--;
    return population[index];
}


unsigned GeneticAlgorithm::calculateDistance(std::vector<int> solution)
{
    unsigned cost = 0;
    for (int i = 0; i < solution.size() - 1; i++)
    {
        cost += roadMap[solution[i]][solution[i + 1]];
    }
    return cost;
}


std::vector<int> GeneticAlgorithm::swapTwoCities(std::vector<int> solution, int swapNumber)
{
    auto newSolution = solution;
    size_t first, second;
    do
    {
        std::random_device randomGenerator;
        std::uniform_int_distribution<int> firstDist(1, solution.size() - 3);
        first = firstDist(randomGenerator);
        std::uniform_int_distribution<int> secondDist(first + 1, solution.size() - 2);
        second = secondDist(randomGenerator);
        std::swap(newSolution[first], newSolution[second]);
    }while(swapNumber--);

    return newSolution;
}


std::vector<int> GeneticAlgorithm::invertSubsolution(std::vector<int> solution)
{
    auto newSolution = solution;
    size_t first, second;
    std::random_device randomGenerator;
    std::uniform_int_distribution<int> firstDist(1, solution.size() - 3);
    first = firstDist(randomGenerator);
    std::uniform_int_distribution<int> secondDist(first + 1, solution.size() - 2);
    second = secondDist(randomGenerator);

    std::reverse(newSolution.begin() + first, newSolution.begin() + second);

    return newSolution;
}


void GeneticAlgorithm::assignRoute(std::vector<int> bestSolution)
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


void GeneticAlgorithm::printPopulation(std::vector<std::vector<int>> population)
{
    for( auto & set : population)
    {
        for( auto & el : set)
            std::cout<< " " << el << " ";
        std::cout<<std::endl;
    }
}


} // namespace tsp
