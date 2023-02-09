#include "pseudo_grid.h"
#include <vector>

/*
 * This class will not be used but the implementation of the method can be copied to the class that will eventually use it
 */

pseudo_grid::pseudo_grid(int _gridSizeX, int _gridSizeY)
{
    this->gridSizeX = _gridSizeX;
    this->gridSizeY = _gridSizeY;
}

std::vector<std::shared_ptr<myTile>> pseudo_grid::getNeighbours(std::shared_ptr<myTile> t){
    std::vector<std::shared_ptr<myTile>> neighbours;

    for(int x = -1; x <=1; x++){
        for(int y = -1; y<=1 ; y++){
            //skip the middle (current) tile and the diagonal tiles
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

            int tempX = t->getXPos() + x;
            int tempY = t->getYPos() + y;

            if(tempX>=0 && tempX<gridSizeX && tempY>=0 && tempY<gridSizeY){
                neighbours.push_back(t);
            }
        }
    }
    return neighbours;
}

void pseudo_grid::setPath(std::vector<std::shared_ptr<myTile>> retracedPath){
    this->path = retracedPath;
}
