#include <iostream>
#include <vector>
#include "helpers/Timer.h"
#include "helpers/RandomNumberGenerator.h"
#include "helpers/FileStream.h"
#include "tests/DataGenerator.h"
#include "tsp/BranchAndBound.h"

using namespace std;
using namespace helpers;
using namespace tests;



int main()
{
    RandomNumberGenerator generator(120000);
    FileStream cokolwiek;
    //DataGenerator::drawData(5, 1000);

    if(!cokolwiek.openFile())
    {
        return -5;
    }

    auto matrix = cokolwiek.readData();
    if(!matrix.size())
    {
        return -5;
    }

    tsp::BranchAndBound test(matrix);
    test.printResult();
    test.computeBestRoute();
    test.printResult();

    return 0;
}
