#include "TabuList.h"
#include "helpers/RandomNumberGenerator.h"

namespace tsp
{

TabuList::TabuList(int size)
    : tabuList(size)
{
    for(auto & row : tabuList)
    {
        row.resize(size);
    }
}



void TabuList::addPenalty(int srcCity, int dstCity)
{
    int penalty = helpers::RandomNumberGenerator(tabuList.size() * tabuList.size()).drawNumber();
    tabuList[srcCity][dstCity] += penalty;
    tabuList[dstCity][srcCity] += penalty;
}

bool TabuList::checkPenalty(int srcCity, int dstCity)
{
    return tabuList[srcCity][dstCity] || tabuList[dstCity][srcCity];
}

void TabuList::reset()
{
    for(auto & row : tabuList)
    {
        for(auto & element : row)
        {
            element = 0;
        }
    }
}

void TabuList::decrement()
{
    for(auto & row : tabuList)
    {
        for(auto & element : row)
        {
            if(element)
            {
               element--;
            }
        }
    }
}

} // namespace tsp
