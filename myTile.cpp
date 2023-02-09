#include "myTile.h"

int myTile::tileID = 0;

myTile::myTile(int xPosition, int yPosition, float tileWeight) : Tile(xPosition, yPosition, tileWeight){
    this->tileID = getTileID();
    incrementTileID();
}


int myTile::getTotalCost()
{
    return hCost + sCost;
}

int myTile::getHeapIndex(){
    return heapIndex;
}

void myTile::setHeapIndex(int x){
    this->heapIndex = x;
}

int myTile::compareTo(std::shared_ptr<myTile> tileToCompare){
    int result = 0;
    if(this->getTotalCost()>tileToCompare->getTotalCost()){
        result = 1;
    }
    if(this->getTotalCost()<tileToCompare->getTotalCost()){
        result = -1;
    }
    if(this->getTotalCost() == tileToCompare->getTotalCost()){
        if(this->hCost > tileToCompare->hCost){
            result = 1;
        }
    }
    return -result;
}

std::shared_ptr<myTile> myTile::getParent(){
    return this->parent;
}

void myTile::setParent(std::shared_ptr<myTile> t){
    this->parent = t;
}

bool myTile::isWalkable(){
    if(this->value>=255){
        return false;
    }
    return true;
}

int myTile::getSCost(){
    return this->sCost;
}

void myTile::setSCost(int newSCost){
    this->sCost = newSCost;
}

void myTile::setHCost(int newHCost){
    this->hCost = newHCost;
}

int myTile::getTileID(){
    return tileID;
}

void myTile::incrementTileID(){
    this->tileID++;
}




