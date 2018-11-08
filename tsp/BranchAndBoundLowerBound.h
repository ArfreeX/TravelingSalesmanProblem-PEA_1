#ifndef BRANCHANDBOUNDLOWERBOUND_H
#define BRANCHANDBOUNDLOWERBOUND_H

#include "tsp/BranchAndBound.h"

namespace tsp
{


class BranchAndBoundLowerBound:
       tsp::BranchAndBound
{
public:
    BranchAndBoundLowerBound(std::vector<std::vector<int>> roadMap);
};

}
#endif // BRANCHANDBOUNDLOWERBOUND_H
