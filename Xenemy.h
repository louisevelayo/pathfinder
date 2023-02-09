#ifndef XENEMY_H
#define XENEMY_H
#include "qtimer.h"
#include "world.h"
#include <iostream>


class Xenemy : public Enemy
{
public:
    Xenemy(int xPosition, int yPosition, float strength);
signals:
    void XEnemyPositionchanged(int x, int y);
};

#endif // XENEMY_H
