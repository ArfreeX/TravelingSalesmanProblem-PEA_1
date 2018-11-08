#include "FileStream.h"

namespace helpers
{

FileStream::~FileStream()
{
    fileRead.close();
    fileWrite.close();
}

bool FileStream::openFile(std::string filename)
{
    if(!filename.empty())
    {
        fileRead.open(filename, std::ios::in);

        if (fileRead.good())
        {
            std::cout << "Done, you can now read the data\n";
            return true;
        }
        return false;
    }

    do
    {
        std::cout << "Insert filename\n";
        std::cin >> filename;
        fileRead.open(filename, std::ios::in);

        if (fileRead.good())
        {
            std::cout << "Done, you can now read the data\n";
            return true;
        }
        else
            std::cout << "File not found, try again or type ""exit"" to leave\n";
    } while (!fileRead.good() && filename != "exit");
    return false;
}

std::vector<std::vector<int>> FileStream::readData()
{
    std::vector<std::vector<int>> roadMap;
    unsigned numberOfCities;
    int weight;

    if (!fileRead.is_open())
    {
        std::cout << "File error - OPEN" << std::endl;
        return roadMap;
    }

    fileRead >> numberOfCities;
    if (fileRead.fail())
    {
        std::cout << "File error - READ NUMBER OF CITIES" << std::endl;
        fileRead.close();
    }

    if (numberOfCities <= 0)
    {
        fileRead.close();
        return roadMap;
    }

    roadMap.resize(numberOfCities);

    for (unsigned i = 0; i < numberOfCities; i++)
    {
        for(unsigned j = 0; j < numberOfCities; j++)
        {
            fileRead >> weight;
            if (fileRead.fail())
            {
                std::cout << "File error - READ WEIGHT" << std::endl;
                break;
            }

            roadMap[i].emplace_back(weight);
        }
    }

    fileRead.close();
    return roadMap;
}

void FileStream::write(std::vector<std::vector<int>> roadMap, std::string filename)
{
    //std::cin >> filename;
    fileWrite.open(filename, std::ios::out);
    fileWrite << roadMap.size() << std::endl;
    for(auto & road : roadMap)
    {
        for(unsigned i = 0; i < roadMap.size(); i++)
        {
            fileWrite << road[i] << " ";
        }
        fileWrite << std::endl;
    }
    fileWrite.close();
}

void FileStream::write(std::vector<long double> timeResults, unsigned dataSize, std::string filename)
{
    fileWrite.open(filename, std::ios::out);
    fileWrite << "Number of cities: " << dataSize << std::endl;
    for(auto & elem : timeResults)
    {
        fileWrite << elem << std::endl;
    }
    fileWrite.close();
}
} // namespace helpers


