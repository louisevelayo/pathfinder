#include "pathfinding.h"
#include <bits/stdc++.h>
#include <fstream>

using namespace std;

Pathfinding::Pathfinding(){}

void Pathfinding::setup(){
    this->tiles = model->getGrid();
    this->enemies = model->getEnemies();
    nrOfTiles = tiles.size();

    this->gridWidth = model->getCol();
    std::cout<< "grid width: " << gridWidth << std::endl;
    this->gridHeight = model->getRows();

    int count = 0;
    for(int i = 0 ; i < nrOfTiles; i++){
        std::shared_ptr<Tile> tile = tiles.at(i);

        TileStruct tileStruct;
        tileStruct.xCord = tile->getXPos();
        tileStruct.yCord = tile->getYPos();
        tileStruct.inClosedSet = false;
        tileStruct.inOpenSet = false;


        std::vector<std::shared_ptr<Enemy>>::iterator enemyIt = enemies.begin(); ;
        while( enemyIt != enemies.end() ){
            int enemyX = (*enemyIt)->getXPos();
            int enemyY = (*enemyIt)->getYPos();
            if ( tileStruct.xCord==enemyX && tileStruct.yCord==enemyY ){
                tileStruct.valueTile = 0.95;
                enemyIt = enemies.erase(enemyIt);
            }else{
                ++enemyIt;
            }
        }

        if(tile->getValue() == std::numeric_limits<float>::infinity()){
            tileStruct.valueTile = -1;
            count++;
        } else{
            tileStruct.valueTile = 1-(tile->getValue());
        }
        gridOfTiles.push_back(tileStruct);
    }
    std::cout << "width = " << this->gridWidth << " height = " << this->gridHeight << " nrOfTiles = " << nrOfTiles << " walls = " << count << std::endl;
}

float Pathfinding::getDistance(TileStruct tileA, TileStruct tileB){
    int dstX = abs(tileA.xCord - tileB.xCord);
    int dstY = abs(tileA.yCord - tileB.yCord);
    return 0.1*dstX + 0.1*dstY;
}

void Pathfinding::findPath()
{

    std::cout << "***Timer started***" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    this->path.clear();

    for(int i = 0 ; i < nrOfTiles; i++){
       auto resetTile = &gridOfTiles[i];
       resetTile->finalCost = 0;
       resetTile->inOpenSet = false;
       resetTile->inClosedSet = false;
       resetTile->lastX = 0;
       resetTile->lastY = 0;
       resetTile->sCost = 0;
       resetTile->hCost = 0;
    }

    std::priority_queue<TileStruct, std::vector<TileStruct>, CompareCost> openSet;
    auto startingTile = &gridOfTiles[getTileIndex(this->startTile.xCord, this->startTile.yCord)];
    startingTile->inClosedSet = false;
    startingTile->inOpenSet = true;
    startingTile->finalCost = 0;
    startingTile->lastX = -1;
    startingTile->lastY = -1;
    startingTile->sCost = 0;
    startingTile->hCost = 0;

    openSet.push(*startingTile);
    while(!openSet.empty()){
        currentTile = openSet.top();
        openSet.pop();
        auto theCurrentTile = &gridOfTiles[getTileIndex(currentTile.xCord, currentTile.yCord)];
        theCurrentTile->inClosedSet = true;

        if(targetReached(currentTile)){
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            cout << duration.count() << " Milliseconds"<< endl;
            return;
        }

        for(int x = -1; x <=1; x++){
            for(int y = -1; y<=1 ; y++){
                if(x==0 && y ==0){
                    continue;
                } if(x==-1 && y==1){
                    continue;
                } if(x==-1 && y==-1){
                    continue;
                } if(x==1 && y==1){
                    continue;
                } if(x==1 && y==-1){
                    continue;
                }
                int tempX = currentTile.xCord + x;
                int tempY = currentTile.yCord + y;

                if(tempX>=0 && tempX<this->gridWidth && tempY>=0 && tempY<this->gridHeight){
                    auto neighbour = &gridOfTiles[getTileIndex(tempX, tempY)];

                    if(neighbour->valueTile<0 || neighbour->inClosedSet){
                        continue;
                    }

                    float newMovementCostToNeighbour = currentTile.sCost + getDistance(currentTile, *neighbour) + 1;

                    if(newMovementCostToNeighbour < neighbour->sCost || !neighbour->inOpenSet){
                        neighbour->sCost = newMovementCostToNeighbour;
                        neighbour->hCost = getDistance(*neighbour, this->endTile);
                        neighbour->finalCost = this->hCostWeight*(neighbour->sCost + neighbour->hCost) + (currentTile.valueTile)*this->sCostWeight;
                        neighbour->lastX = currentTile.xCord;
                        neighbour->lastY = currentTile.yCord;
                        neighbour->inOpenSet = true;
                        openSet.push(*neighbour);
                    }
                }
            }
        }
    }
}

std::vector<TileStruct> Pathfinding::getPath(){
    std::vector<TileStruct> path;
    int endX = this->endTile.xCord;
    int endY = this->endTile.yCord;
    auto currentTile = &gridOfTiles[getTileIndex(endX, endY)];
    if(currentTile == NULL) return path;

    while((currentTile->xCord!=this->startTile.xCord) || (currentTile->yCord!=this->startTile.yCord)){
      path.push_back(*currentTile);
      int nextTileX = currentTile->lastX;
      int nextTileY = currentTile->lastY;
      currentTile = &gridOfTiles[getTileIndex(nextTileX, nextTileY)];
    }
    std::reverse(path.begin(), path.end());

    return path;
}


int Pathfinding::setStartWithCoords(int posX, int posY){
    auto tempTile = &gridOfTiles[getTileIndex(posX, posY)];
    if(tempTile->valueTile == -1){
        return -1;
    }
    TileStruct startTileTemp;
    startTileTemp.xCord = posX;
    startTileTemp.yCord = posY;

    this->startTile = startTileTemp;

    return 0;
}


int Pathfinding::setTargetWithCoords(int posX, int posY){
    auto tempTile = &gridOfTiles[getTileIndex(posX, posY)];
    if(tempTile->valueTile == -1){
        return -1;
    }
    if(posX<0 || posY<0 || posX>gridWidth || posY>gridHeight){
        return -2;
    }
    TileStruct endTileTemp;
    endTileTemp.xCord = posX;
    endTileTemp.yCord = posY;

    this->endTile = endTileTemp;

    return 0;
}

bool Pathfinding::targetReached(TileStruct tileToCheck){
    if(tileToCheck.xCord == this->endTile.xCord && tileToCheck.yCord == this->endTile.yCord){
        return true;
    }
    return false;
}

void Pathfinding::setModel(Model *model){
    this->model = model;
}

int Pathfinding::getTileIndex(int x, int y){
    return y * gridWidth + x;
}

void Pathfinding::setWeight(const float heuristicWeight){
    float temp = heuristicWeight;
    if (temp >= 1){
        temp = 1;
    } if (temp <= 0){
        temp = 0;
    } else{
        temp = log10(1+heuristicWeight);
    }

    this->sCostWeight = 1-temp;
    this->hCostWeight = temp;
}










