#ifndef PATHFINDING_H
#define PATHFINDING_H
#include "world.h"
#include "Model.h"
#include "tile_struct.h"
#include <iostream>
#include <set>
#include <vector>
#include <cstdlib>
#include <unordered_set>


class Pathfinding
{
public:
    Pathfinding();

    void findPath();
    float getDistance(TileStruct tileA, TileStruct tileB);
    void setup();
    std::string serialize();
    std::vector<TileStruct> getNeighbours(TileStruct currentTile);

    bool targetReached(TileStruct tileToCheck);

    void setModel(Model *model);

    int setTargetWithCoords(int posX, int posY);

    int setStartWithCoords(int posX, int posY);

    int getTileIndex(int x, int y);

    void setWeight(const float heuristicWeight);


    std::vector<TileStruct> getPath();

private:
    TileStruct startTile;
    TileStruct endTile;
    std::vector<std::shared_ptr<Tile>> tiles;
    int nrOfTiles;
    struct CompareCost {
        bool operator()(TileStruct const& t1, TileStruct const& t2)
        {
            // return "true" if "t1" is ordered
            // before "t2"
            return t1.finalCost > t2.finalCost;
        }
    };
    std::vector<TileStruct> path;
    Model *model;
    std::vector<TileStruct>gridOfTiles;
    std::vector<std::shared_ptr<Enemy>> enemies;


    float hCostWeight;
    float sCostWeight;
    float stepCost;
    int gridWidth;
    int gridHeight;
    int realWidth;
    int realHeight;
    TileStruct currentTile;
};

#endif // PATHFINDING_H
