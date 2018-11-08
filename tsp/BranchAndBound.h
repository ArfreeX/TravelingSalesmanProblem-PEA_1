#pragma once
#ifndef TSPBRANCHANDBOUND_H
#define TSPBRANCHANDBOUND_H

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cstring>
#include <climits>

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

protected:
    struct Node
    {
        std::vector<std::pair<int, int>> route;
        std::vector<std::vector<int>> reducedMatrix;

        int cost;
        int currentCity;
        int level;
    };

    struct comp {
        bool operator()(const Node* lhs, const Node* rhs) const
        {
            return lhs->cost > rhs->cost;
        }
    };

    Node* newNode(std::vector<std::vector<int>> & parentVector, std::vector<std::pair<int, int>> const &path,
                int level, int i, int j);
    void rowReduction(std::vector<std::vector<int>> & reducedMatrix, std::vector<int> & row);
    void columnReduction(std::vector<std::vector<int>> & reducedMatrix, std::vector<int> & col);
    int calculateCost(std::vector<std::vector<int>> & reducedMatrix);
    void cleanQueue(int level);

    std::vector<std::pair<int, int>> route;
    unsigned numberOfCities = 0;
    std::priority_queue<Node*, std::vector<Node*>, comp> livingNodes;
private:
    int solve(std::vector<std::vector<int>> & costMatrix);

};

} // namespace tsp
#endif // TSPBRANCHANDBOUND_H
