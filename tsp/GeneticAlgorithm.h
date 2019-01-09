#pragma once
#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <list>
#include "GenericTsp.h"
#include "helpers/Timer.h"

namespace tsp
{

class GeneticAlgorithm :
    public GenericTsp
{
public:
//    enum CrossingStrategy: uint8_t
//    {
//        INSERT,
//        SWAPP,
//        UNCHECKED
//    };

    enum MutatingStrategy: uint8_t
    {
        INVERT,
        SWAP,
        UNCHECKED
    };

    enum CrossingStrategy: uint8_t
    {
        SUBSET,
        COINFLIP,
        NONE
    };

    //tsp::GeneticAlgorithm::CrossingStrategy tspCrossingStrategy;

    GeneticAlgorithm(std::vector<std::vector<int>> roadMap, long long int timeLimit,
                       tsp::GeneticAlgorithm::MutatingStrategy tspMutatingStrategy,
                       tsp::GeneticAlgorithm::CrossingStrategy tspCrossingStrategy,
                       int population, int crossingFactor, int mutationFactor);

    ~GeneticAlgorithm();

    void computeBestRoute();
    void printPopulation(std::vector<std::vector<int>> population);
private:
    void createRandomPopulation();
    unsigned calculateDistance(std::vector<int> solution);
    std::vector<int> swapTwoCities(std::vector<int> solution, int swapNumber = 0);
    void assignRoute(std::vector<int> bestSolution);
    void normalizeFitness();
    std::vector<std::vector<int>> nextGeneration(std::vector<std::vector<int>> &population);
    std::vector<int> invertSubsolution(std::vector<int> solution);
    std::vector<int> pickOne();
    std::vector<int> mutate(std::vector<int> order);
    std::vector<int> crossover(std::vector<int> processingOrderA, std::vector<int> processingOrderB);
    std::vector<int> crossCoinFlip(std::vector<int> processingOrderA, std::vector<int> processingOrderB);
    std::vector<int> crossWithSubset(std::vector<int> processingOrderA, std::vector<int> processingOrderB);

    int populationSize;
    float crossingFactor, mutationFactor;
    unsigned numbOfCities;
    long long int timeLimit;
    std::vector<int> processingSolution;
    std::vector<std::vector<int>> population;
    std::vector<double> fitness;
    MutatingStrategy tspMutatingStrategy;
    CrossingStrategy tspCrossingStrategy;
};

} // namespace tsp
#endif // GENETICALGORITHM_H
