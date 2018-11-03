#pragma once
#ifndef TSPBRANCHANDBOUND_H
#define TSPBRANCHANDBOUND_H

#include "GenericTsp.h"

namespace tsp
{

class BranchAndBound :
    public GenericTsp
{
public:
    BranchAndBound(std::vector<std::vector<int>> roadMap);
    ~BranchAndBound();
    void computeBestRoute();
};

} // namespace tsp
#endif // TSPBRANCHANDBOUND_H
