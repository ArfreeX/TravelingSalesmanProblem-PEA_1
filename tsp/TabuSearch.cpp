#include "TabuSearch.h"


namespace tsp
{

TabuSearch::TabuSearch(std::vector<std::vector<int>> roadMap, long long int timeLimit)
    : GenericTsp (roadMap),
      timeLimit(timeLimit),
      numbOfCities(roadMap.size())
{
    if(!roadMap.size())
    {
        return;
    }

    tabuList = std::vector<std::vector<int>>(numbOfCities);
    for(unsigned i = 0 ; i < numbOfCities; i++)
    {
        tabuList[i].resize(numbOfCities);
    }
    resetTabuList();
    numberOfIterations = numbOfCities * 100;
    setupCurrentSolution();
    setupBestSolution();

}

TabuSearch::~TabuSearch()
{

}

void TabuSearch::resetTabuList()
{
    for(int i = 0; i < tabuList.size(); i++)
    {
        for(int j = 0; j < tabuList.size(); j++)
        {
            tabuList[i][j] = 0 ;
        }
    }
}

void TabuSearch::computeBestRoute()
{
    helpers::Timer time;
    std::vector<int> processingSolution = currSolution;
    time.start();
    int counter = 0;
    int counterLoop = 0;
    while ( time.elapsed() < timeLimit )
    {
        int city1 = -1;
        int city2 = -1;
        currSolution = processingSolution;
        for (int j = 1; j < currSolution.size() - 1; j++)
        {
            for (int k = j + 1; k < currSolution.size() - 1; k++)
            {
                std::swap(currSolution[j], currSolution[k]);
                int currCost = calculateDistance(currSolution);
                if((currCost < minRouteWeight))
                {
                    counter++;
                    if(tabuList[j][k])
                        counterLoop++;
                }
                if ((currCost < minRouteWeight) && tabuList[j][k])
                {
                    city1 = j;
                    city2 = k;
                    bestSolution = currSolution;
                    minRouteWeight = currCost;

                    helpers::RandomNumberGenerator randomizer(numbOfCities*numbOfCities);
                    int penalty = randomizer.drawNumber();
                    tabuList[city1][city2] = penalty;
                    tabuList[city2][city1] = penalty;
                }
//                else
//                {
//                    currSolution = swap(j, k, currSolution);
//                }
            }
        }

       //if(city1 != -1)
            //decrementTabu();
    }
    std::cout<<"Counter swap: "<< counter << " Counter loop: " << counterLoop << std::endl << std::endl;
//    for(int i = 0; i < tabuList.size(); i++)
//    {
//        for(int j = 0; j < tabuList.size(); j++)
//        {
//            std::cout << tabuList[i][j] << " ";
//        }
//    }
    assignRoute(bestSolution);
}

void TabuSearch::setupBestSolution()
{
    bestSolution = currSolution;
    minRouteWeight = calculateDistance(bestSolution);
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

void TabuSearch::setupCurrentSolution()
{
    currSolution = std::vector<int>(numbOfCities + 1);
    for (int i = 0; i < numbOfCities; i++)
    {
        currSolution[i] = i;
    }
    currSolution[numbOfCities] = 0;
}

void TabuSearch::tabuMove(int city1, int city2)
{ //tabus the swap operatio
    helpers::RandomNumberGenerator randomizer(numbOfCities*numbOfCities);
    int penalty = randomizer.drawNumber();
    tabuList[city1][city2] = penalty;
    tabuList[city2][city1] = penalty;

}

void TabuSearch::decrementTabu()
{
    for(int i = 0; i < tabuList.size(); i++)
    {
        for(int j = 0; j < tabuList.size(); j++)
        {
            if(tabuList[i][j] > 0)
                tabuList[i][j] = tabuList[i][j] - 1;
        }
    }
}

unsigned TabuSearch::calculateDistance(std::vector<int> solution)
{
    unsigned cost = 0;
    for (int i = 0; i < solution.size() - 1; i++) {
        cost += roadMap[solution[i]][solution[i + 1]];
    }
    return cost;
}

//std::vector<int> TabuSearch::swap(int i, int k, std::vector<int> solution)
//{
//    int temp = solution[i];
//    solution[i] = solution[k];
//    solution[k] = temp;

//    return solution;
//}

} // namespace tsp
