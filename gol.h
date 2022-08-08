#pragma once

#include <iostream>
#include <stdint.h>
#include <unordered_set>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <random>
#include <cmath>

using namespace std;

class GOL
{
    struct pairHash
    {
        size_t operator () (pair<int64_t, int64_t> const &pair) const
        {
            return (hash<int64_t>()(pair.first) << 6) ^ (hash<int64_t>()(pair.second) >> 2);
        }
    };

    typedef pair<int64_t, int64_t> coords;
    typedef unordered_set<coords, pairHash> universe;

    universe board;
    vector<coords> inFrame;

    unsigned int windowWidth, windowHeight;

    bool isAlive(const int64_t &x, const int64_t &y);
    int getLiveNeighborCount(const int64_t &x, const int64_t &y);
    void putDeadNeighbors(const int64_t &x, const int64_t &y, vector<coords> &deadNeighbors);
    void prepareFrame(const coords &xy, const int64_t &xBound, const int64_t &yBound);

    public:
    GOL();
    GOL(string fileName);
    void step();
    vector<coords> getElementsInFrame();
    void setWidth(unsigned int width);
    void setHeight(unsigned int height);
    void generateTestFile(string fileName, const int64_t &lowerRange, const int64_t &upperRange, const int64_t &aliveCount);
    void loadFile(string fileName);
    void writeToFile(string fileName);
};