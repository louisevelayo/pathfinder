#ifndef POISONOUSTILE_H
#define POISONOUSTILE_H
#include "world.h"


class poisonousTile: public Tile, public QObject
{
public:
    poisonousTile(int xPosition, int yPosition, float tileWeight);

signals:
  void isactivated();
};

#endif // POISONOUSTILE_H
