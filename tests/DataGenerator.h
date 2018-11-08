#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include <limits.h>
#include "helpers/FileStream.h"
#include "helpers/RandomNumberGenerator.h"

namespace tests {

class DataGenerator
{
public:
    static std::vector<std::vector<int>> drawData(unsigned dataSize, unsigned dataRange)
    {
        helpers::FileStream file;
        helpers::RandomNumberGenerator numberGen(dataRange);
        std::vector<std::vector<int>> dataSet(dataSize);

        for (unsigned i = 0; i < dataSize; i++)
        {
            for(unsigned j = 0; j < dataSize; j++)
            {
                if(i == j)
                {
                    dataSet[i].emplace_back(0);
                }
                else
                {
                    dataSet[i].emplace_back(numberGen.drawNumber());
                }
            }
        }

        return dataSet;
    }
};
} // namespace tests
#endif // DATAGENERATOR_H
