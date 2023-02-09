#include "potionview.h"


potiontileView::potiontileView(int size, int x, int y)
{
    tileSize = size;
    potion = new QGraphicsPixmapItem(QPixmap(":/world_images/potion-icon-png-15614.png").scaled(tileSize,tileSize), this);
    potion->setZValue(8);
    potion->setPos(x,y);
    potion->setVisible(true);

    deadpotion = new QGraphicsPixmapItem(QPixmap(":/world_images/potion.png").scaled(tileSize,tileSize),this);
    deadpotion->setZValue(7);
    deadpotion->setPos(x,y);
    deadpotion->setVisible(false);

    drinked = 0;
}

int potiontileView::getDrinked() const
{
    return drinked;
}

void potiontileView::updatedrinked()
{
    potion->setVisible(false);
    drinked = 1;
}


