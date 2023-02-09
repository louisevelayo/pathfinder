#ifndef HEAP_H
#define HEAP_H
#include "myTile.h"
#include <vector>
#include <memory>




class heap
{
public:
    heap();
    heap(int maxHeapSize);

    //method that adds a node to the tree
    void add(std::shared_ptr<myTile> t);

    //method to retreive the root of the tree -> this would be the tile with the lowest total cost
    std::shared_ptr<myTile> removeFirst();

    //used to update the nodes position in the binary tree
    void updateItem(std::shared_ptr<myTile> t);

    //used to check if the tile in question is also in the heap data structure
    bool contains(std::shared_ptr<myTile> t);

    //sorting algorithm - used to move a node up the binary tree if its value is less than its parents
    void sortUp(std::shared_ptr<myTile> t);

    //sorting algorithm - used to move a node down a binary tree if its value is more than one of its children
    void sortDown(std::shared_ptr<myTile> t);

    int getTileCount();

    void swap(std::shared_ptr<myTile> t1, std::shared_ptr<myTile> t2);

    std::string serialize();
private:
    int tileCount = 0;
    int heapSize;
    //std::vector<std::shared_ptr<tile>> tiles;
};

#endif // HEAP_H
