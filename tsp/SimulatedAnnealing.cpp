#include "SimulatedAnnealing.h"
#include <math.h>

namespace tsp
{

SimulatedAnnealing::SimulatedAnnealing(std::vector<std::vector<int>> roadMap, long long int timeLimit)
    : GenericTsp (roadMap),
      timeLimit(timeLimit)
{

}

SimulatedAnnealing::~SimulatedAnnealing()
{

}

int SimulatedAnnealing::getTotalDistance(std::vector<int> order)
{
    double sum = 0;;
    for (int i = 0; i < order.size() - 1; i++)
    {
        sum += roadMap[order[i]][order[i + 1]];
    }
    sum += roadMap[order[0]][order[order.size()-1]];
    return sum;
}

void SimulatedAnnealing::computeBestRoute()
{
    int iteration = -1;
        std::vector<int> actualOrder(roadMap.size());
        double temperature = 10000.0;
        double deltaDistance = 0;
        double coolingRate = 0.9999;
        double absoluteTemperature = 0.000000001;
        double shortestDistance;
        int lastSwaped =  0;

        for (int i = 0; i < actualOrder.size(); i++)
            actualOrder[i] = i;

        double distance = getTotalDistance(actualOrder);

        while (temperature > absoluteTemperature)
        {

            std::vector<int> nextOrder(actualOrder);


            //losowanie zamiany
            int index1 = rand() % actualOrder.size();
            int index2 = rand() % actualOrder.size();
            int tmp = nextOrder[index1];
            nextOrder[index1] = nextOrder[index2];
            nextOrder[index2] = tmp;
            lastSwaped++;

            //obliczamy roznice odleglosci nowej sciezki
            deltaDistance = getTotalDistance(nextOrder) - distance;

            //jesli jest mniejsza
            //albo wieksza, ale i spelnia prawdpodobienstwo Boltzmana

            if ((deltaDistance < 0) || (distance > 0 &&
                exp(-deltaDistance / temperature) > rand()))
            {
                //przepisujemy nowe rozwiazanie
                for (int i = 0; i < actualOrder.size(); i++)
                    actualOrder[i] = nextOrder[i];

                distance = deltaDistance + distance;
                lastSwaped = 0;
            }

            //obnizamy "temperature"
            temperature *= coolingRate;

            iteration++;
        }
        minRouteWeight = distance;
}

} // namespace tsp
