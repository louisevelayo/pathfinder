#ifndef MYTILE_H
#define MYTILE_H
#include "world.h"
#include <memory>
#include <iostream>
#include <stdexcept>
#include <string>

class myTile: public Tile
{

using Tile::Tile;


private:
    int sCost;  //Start Cost - This is the distance from the starting node
    int hCost;  //Heuristic Cost - This is the distance from the end node
    int heapIndex;
    static int tileID;
    std::shared_ptr<myTile> parent;

public:
    //myTile(int xPosition, int yPosition, float tileWeight) : Tile(xPosition, yPosition, tileWeight){}
    myTile(int xPosition, int yPosition, float tileWeight);
    myTile();
    bool isWalkable();
    int getTotalCost();
    int getHeapIndex();
    void setParent(std::shared_ptr<myTile> t);
    void setHeapIndex(int x);
    std::shared_ptr<myTile> getParent();
    int compareTo(std::shared_ptr<myTile> tileToCompare);
    int getSCost();
    void setSCost(int newSCost);
    void setHCost(int newHCost);
    void incrementTileID();
    int getTileID();


//private:
//    int sCost;  //Start Cost - This is the distance from the starting node
//    int hCost;  //Heuristic Cost - This is the distance from the end node
//    int heapIndex;
//    static int tileID;
//    std::shared_ptr<myTile> parent;
};



#endif // MYTILE_H
