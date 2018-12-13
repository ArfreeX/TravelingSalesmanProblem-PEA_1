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

void TabuList::penalize(int srcCity, int dstCity)
{
    int penalty = helpers::RandomNumberGenerator(tabuList.size()*10).drawNumber() + 1;
    tabuList[srcCity][dstCity] += penalty;
    tabuList[dstCity][srcCity] += penalty;
}

bool TabuList::isPenalized(int srcCity, int dstCity)
{
    return tabuList[srcCity][dstCity];
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
