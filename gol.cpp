#include "gol.h"

GOL::GOL()
{

}

GOL::GOL(string fileName)
{
    loadFile(fileName);
}

bool GOL::isAlive(const int64_t &x, const int64_t &y)
{
    if (board.find({x, y}) != board.end())
        return true;
    return false;
}

int GOL::getLiveNeighborCount(const int64_t &x, const int64_t &y)
{
    int liveNeighbors = 0;
    vector<pair<int, int>> adjacentCells = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}};

    for (const pair<int, int> &adjacentCell : adjacentCells)
            if (isAlive(x - adjacentCell.first, y - adjacentCell.second))
                liveNeighbors++;
                
    return liveNeighbors;
}

void GOL::putDeadNeighbors(const int64_t &x, const int64_t &y, vector<coords> &deadNeighbors)
{
    vector<pair<int, int>> adjacentCells = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}};
    deadNeighbors = {};
    for (const pair<int, int> &adjacentCell : adjacentCells)
    {
        int64_t x1 = x - adjacentCell.first, y1 = y - adjacentCell.second;

        if (!isAlive(x1, y1))
            deadNeighbors.push_back({x1, y1});
    }
}

void GOL::prepareFrame(const coords &xy, const int64_t &xBound, const int64_t &yBound)
{
    if (xy.first > -1*xBound/2 && xy.first < xBound/2 && xy.second > -1*yBound/2 && xy.second < yBound/2)
            inFrame.push_back({xy.first+xBound/2, xy.second+yBound/2});
}

void GOL::setWidth(unsigned int width)
{
    windowWidth = width;
}

void GOL::setHeight(unsigned int height)
{
    windowHeight = height;
}

void GOL::step()
{
    universe nextStep;
    vector<coords> deadNeighbors;
    inFrame = {};
    for (const coords &xy : board)
    {
        prepareFrame(xy, windowWidth/4, windowHeight/4);
        putDeadNeighbors(xy.first, xy.second, deadNeighbors);
        int size = deadNeighbors.size();
        if (size == 5 || size == 6) //cell will stay alive, so we advance it
            nextStep.insert(xy);
        for (const coords &deadNeighbor : deadNeighbors)
            if (getLiveNeighborCount(deadNeighbor.first, deadNeighbor.second) == 3) //cell will be alive
                nextStep.insert(deadNeighbor);
    }
    board = nextStep;
}

vector<GOL::coords> GOL::getElementsInFrame()
{
    return inFrame;
}

void GOL::generateTestFile(string fileName, const int64_t &lowerRange, const int64_t &upperRange, const int64_t &aliveCount)
{
    ofstream testFile(fileName);
    testFile << "#RIOT INPUT FORMAT\n";
    ofstream life106("LIFE106 "+fileName);
    life106 << "#Life 1.06\n";

    random_device rd;
    mt19937_64 mt(rd());
    uniform_int_distribution<long long int> dist(lowerRange, upperRange);
    
    for (int i = 0; i < aliveCount; i++)
    {
        int64_t randx = dist(mt), randy = dist(mt);
        testFile << "(" << randx << ", " << randy << ")" << endl;
        life106 << randx << " " << randy << endl;
    }
}

void GOL::loadFile(string fileName)
{
    ifstream file(fileName);
    string line;

    getline(file, line); //discard the header
    while (getline(file, line))
        board.insert({stoll(line.substr(1, line.find(",")-1)), stoll(line.substr(line.find(", ")+2, line.size()-1))});
}

void GOL::writeToFile(string fileName)
{
    ofstream output(fileName);
    output << "#Life 1.06\n";
    for (const coords &xy : board)
        output << xy.first << " " << xy.second << endl;
}