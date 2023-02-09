#include "normalennemyview.h"

normalEnnemyView::normalEnnemyView(int size, int x, int y, int value)
{
    tileSize = size;
    ennemy = new QGraphicsPixmapItem(QPixmap(":/world_images/amongus.png").scaled(tileSize,tileSize), this);
    ennemy->setZValue(8);
    ennemy->setPos(x,y);
    ennemy->setVisible(true);

    deadennemy = new QGraphicsPixmapItem(QPixmap(":/world_images/deadamongus.png").scaled(tileSize,tileSize), this);
    deadennemy->setZValue(8);
    deadennemy->setPos(x,y);
    deadennemy->setVisible(false);

    strenght= new QGraphicsTextItem(QString::number(value), this);
    strenght->setPos(x+tileSize/5,y-tileSize/2);
    strenght->setDefaultTextColor("green");
}

void normalEnnemyView::ondead()
{
    ennemy->setVisible(false);
    strenght->setVisible(false);
    deadennemy->setVisible(true);
}
