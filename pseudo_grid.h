#ifndef PSEUDO_GRID_H
#define PSEUDO_GRID_H
#include "myTile.h"
#include <vector>
#include <memory>

class pseudo_grid
{
public:
    pseudo_grid(int _gridSizeX, int _gridSizeY);

    //method to check the immediate north, south, east and west neighbour
    std::vector<std::shared_ptr<myTile>> getNeighbours(std::shared_ptr<myTile> t);
    void setPath(std::vector<std::shared_ptr<myTile>> retracedPath);
    std::string serialize();
private:
    int gridSizeX, gridSizeY;
    std::vector<std::shared_ptr<myTile>> path;
};

#endif // PSEUDO_GRID_H
