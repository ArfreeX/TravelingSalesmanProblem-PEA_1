#pragma once
#ifndef FILESTREAM_H
#define FILESTREAM_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace helpers
{

class FileStream
{
public:
    ~FileStream();
    bool openFile(std::string filename = "");
    void readStart(int &edges, int &vertexs, int &starting, int &ending);
    std::vector<std::vector<int>> readData();
    void write(std::vector<std::vector<int>> array);

private:
    std::ifstream fileRead; // odczyt z pliku
    std::ofstream fileWrite; // wypis do pliku ( wypis wynikow )
    std::string filename; // pole z nazwa pliku
};

} // namespace helpers
#endif // FILESTREAM_H
