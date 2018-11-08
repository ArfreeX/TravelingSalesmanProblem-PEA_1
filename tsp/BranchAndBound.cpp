#include "BranchAndBound.h"

namespace tsp
{

BranchAndBound::BranchAndBound(std::vector<std::vector<int>> roadMap)
    : GenericTsp(roadMap)
{
    if(roadMap.empty() || roadMap.size() > 25)
    {
        return;
    }
    numberOfCities = roadMap.size();

    for(auto & line : roadMap)
    {
        for(auto & element : line)
        {
            if(element == 0)
            {
                element = INT_MAX;
            }
        }
    }
}

BranchAndBound::~BranchAndBound()
{
    while(!livingNodes.empty())
    {
        auto node = livingNodes.top();
        livingNodes.pop();
        delete node;
    }
}

BranchAndBound::Node* BranchAndBound::newNode(std::vector<std::vector<int>> & ancestorMatrix,
    std::vector<std::pair<int, int>> const & ancestorPath,int level, int ancestorCity, int currentCity)
{
    Node* node = new Node;

    node->route = ancestorPath;

    if (level != 0)
    {
        node->route.push_back(std::make_pair(ancestorCity, currentCity));
    }

    node->reducedMatrix = ancestorMatrix;

    if(level)
    {
        for (unsigned i = 0; i < numberOfCities; i++)
        {
            node->reducedMatrix[ancestorCity][i] = INT_MAX;
            node->reducedMatrix[i][currentCity] = INT_MAX;
        }
    }

    node->reducedMatrix[currentCity][0] = INT_MAX;
    node->level = level;
    node->currentCity = currentCity;

    return node;
}

void BranchAndBound::rowReduction(std::vector<std::vector<int>> & reducedMatrix, std::vector<int> & row)
{
    std::fill(row.begin(), row.end(), INT_MAX);

    for (unsigned i = 0; i < numberOfCities; i++)
    {
        for (unsigned j = 0; j < numberOfCities; j++)
        {
            if (reducedMatrix[i][j] < row[i])
            {
                row[i] = reducedMatrix[i][j];
            }
        }
    }

    for (unsigned i = 0; i < numberOfCities; i++)
    {
        for (unsigned j = 0; j < numberOfCities; j++)
        {
            if (reducedMatrix[i][j] != INT_MAX && row[i] != INT_MAX)
            {
                reducedMatrix[i][j] -= row[i];
            }
        }
    }
}

void BranchAndBound::columnReduction(std::vector<std::vector<int>> & reducedMatrix, std::vector<int> & col)
{
    std::fill(col.begin(), col.end(), INT_MAX);

    for (unsigned i = 0; i < numberOfCities; i++)
    {
        for (unsigned j = 0; j < numberOfCities; j++)
        {
            if (reducedMatrix[i][j] < col[j])
            {
                col[j] = reducedMatrix[i][j];
            }
        }
    }

    for (unsigned i = 0; i < numberOfCities; i++)
    {
        for (unsigned j = 0; j < numberOfCities; j++)
        {
            if (reducedMatrix[i][j] != INT_MAX && col[j] != INT_MAX)
            {
                reducedMatrix[i][j] -= col[j];
            }
        }
    }
}

int BranchAndBound::calculateCost(std::vector<std::vector<int>> & reducedMatrix)
{
    int cost = 0;

    std::vector<int> row(numberOfCities);
    rowReduction(reducedMatrix, row);

    std::vector<int> col(numberOfCities);
    columnReduction(reducedMatrix, col);

    for (int i = 0; i < numberOfCities; i++)
    {
        cost += (row[i] != INT_MAX) ? row[i] : 0,
            cost += (col[i] != INT_MAX) ? col[i] : 0;
    }

    return cost;
}

void BranchAndBound::cleanQueue(int level)
{
    std::vector<Node*> temp;
    while(!livingNodes.empty())
    {
        temp.emplace_back(livingNodes.top());
        livingNodes.pop();
    }

    for(int i = 0; i < temp.size(); i++)
    {
        if( temp[i]->level < level - 3 )
        {
            delete temp[i];
        }
        else
        {
            livingNodes.push(temp[i]);
        }
    }


}

int BranchAndBound::solve(std::vector<std::vector<int>> & costMatrix)
{
    Node* root = newNode(costMatrix, std::vector<std::pair<int, int>>(), 0, -1, 0);

    root->cost = calculateCost(root->reducedMatrix);

    livingNodes.push(root);

    while (!livingNodes.empty())
    {
        Node* min = livingNodes.top();
        livingNodes.pop();
        cleanQueue(min->level);
        int currentCity = min->currentCity;

        if (min->level == numberOfCities - 1)
        {
            min->route.push_back(std::make_pair(currentCity, 0));
            this->route = min->route;

            int cost = min->cost;

            return cost;
        }

        for (int cityToVisit = 0; cityToVisit < numberOfCities; cityToVisit++)
        {
            if (min->reducedMatrix[currentCity][cityToVisit] != INT_MAX)
            {
                Node* child = newNode(min->reducedMatrix, min->route,
                                min->level + 1, currentCity, cityToVisit);

                child->cost = min->cost + min->reducedMatrix[currentCity][cityToVisit]
                                + calculateCost(child->reducedMatrix);

                livingNodes.push(child);
            }
        }
        delete min;
    }
}

void BranchAndBound::computeBestRoute()
{
    if(!numberOfCities)
    {
        return;
    }

    minRouteWeight = solve(roadMap);
    unsigned i;
    for(i = 1; i < route.size(); i++)
    {
        bestRoute[i][0] = route[i-1].second;
        bestRoute[i][1] = roadMap[bestRoute[i - 1][0]][bestRoute[i][0]];
    }
    bestRoute[i][1] = roadMap[bestRoute[i - 1][0]][bestRoute[i][0]];
}

} // namespace tsp

