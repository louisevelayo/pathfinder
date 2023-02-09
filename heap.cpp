#include "heap.h"

std::shared_ptr<myTile> tiles[] = {};

heap::heap(){}

heap::heap(int maxHeapSize)
{
    tiles[maxHeapSize] = {};
}

void heap::add(std::shared_ptr<myTile>  t)
{
    t->setHeapIndex(tileCount);
    tiles[tileCount] = t;
    sortUp(t);
    tileCount++;
}

std::shared_ptr<myTile> heap::removeFirst(){
    std::shared_ptr<myTile> headNode = tiles[0];
    tileCount--;
    tiles[0] = tiles[tileCount];
    std::shared_ptr<myTile>  temp = tiles[0];
    temp->setHeapIndex(0);
    sortDown(temp);
    return headNode;
}

bool heap::contains(std::shared_ptr<myTile> t){
    return (tiles[t->getHeapIndex()]->getTotalCost() == t->getTotalCost());
}

void heap::updateItem(std::shared_ptr<myTile> t){
    sortUp(t);
}

void heap::sortUp(std::shared_ptr<myTile> t){
    int parentIndex = (t->getHeapIndex()-1)/2;

    while(true){
        std::shared_ptr<myTile> parentTile = tiles[parentIndex];
        //check if the parent node has a higher cost than current node
        if(t->compareTo(parentTile)>0){
            swap(t, parentTile);
        } //if not, node is in the right place and we exit the loop
        else{
            break;
        } //we need to update the heap index after the swap.
        parentIndex = (t->getHeapIndex()-1)/2;
    }

}

void heap::sortDown(std::shared_ptr<myTile> t){
    while(true){
        int leftChildIndex = t->getHeapIndex()*2 + 1;
        int rightChildIndex = t->getHeapIndex()*2 + 2;
        int swapIndex = 0;

        //determine if there are child nodes
        if(leftChildIndex < tileCount){
            swapIndex = leftChildIndex;

            if(rightChildIndex < tileCount){
                int compareVal = tiles[leftChildIndex]->compareTo(tiles[rightChildIndex]);
                if(compareVal<0){
                    swapIndex = rightChildIndex;
                }
            } if(t->compareTo(tiles[swapIndex])<0){
                swap(t, tiles[swapIndex]);
            }
            else{
                return;
            }
        } else{
            return;
        }
    }
}

void heap::swap(std::shared_ptr<myTile> t1, std::shared_ptr<myTile> t2){
    int tempIndex = t1->getHeapIndex();
    tiles[t1->getHeapIndex()] = t2;
    tiles[t2->getHeapIndex()] = t1;
    t1->setHeapIndex(t2->getHeapIndex());
    t2->setHeapIndex(tempIndex);
}

int heap::getTileCount(){
    return this->tileCount;
}

