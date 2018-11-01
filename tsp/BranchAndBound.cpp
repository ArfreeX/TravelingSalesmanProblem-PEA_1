#include "BranchAndBound.h"

namespace tsp
{

BranchAndBound::BranchAndBound(std::vector<std::vector<int>> roadMap)
    : GenericTsp(roadMap) {};

BranchAndBound::~BranchAndBound()
{
}


void BranchAndBound::computeBestRoute()
{
    for ( unsigned i = 0 ; i < 5 ; i++)
    {
        bestRoute[i][0] = static_cast<int>(i);
        bestRoute[i][1] = roadMap[i][0];
        routeWeight += roadMap[i][0];
    }

}

} // namespace tsp

