#ifndef TILE_STRUCT_H
#define TILE_STRUCT_H

#endif // TILE_STRUCT_H

struct TileStruct{
    //std::shared_ptr<PlannerNode> m_pParent; //men path
    int xCord, yCord;
    float finalCost;
    float hCost;
    float sCost;
    float valueTile;
    int lastX;
    int lastY;
    bool inOpenSet;
    bool inClosedSet;


};
