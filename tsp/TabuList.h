#ifndef TABULIST_H
#define TABULIST_H
#include <vector>

namespace tsp
{

class TabuList
{
public:
    TabuList(int size);

    void addPenalty(int srcCity, int dstCity);

    bool checkPenalty(int srcCity, int dstCity);

    void reset();

    void decrement();

private:
    std::vector<std::vector<int>> tabuList;
};

} // namespace tsp
#endif // TABULIST_H
