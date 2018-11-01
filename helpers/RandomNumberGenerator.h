#pragma once
#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H

#include <random>

namespace helpers
{

class RandomNumberGenerator // source http://antoni.sterna.staff.iiar.pwr.wroc.pl/sdizo/SDiZO_random.pdf
{
public:
    RandomNumberGenerator(int maxRand) :
        gen(rd()),
        dist(1, maxRand)
    {}

    int drawNumber()
    {
        return dist(gen);
    }

private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist;
};

} // namespace helpers
#endif // RANDOMNUMBERGENERATOR_H
