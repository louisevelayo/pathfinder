#include "Xenemyview.h"
#include "normalennemyview.h"

XEnemyView::XEnemyView(int size, int x, int y, int value)
{
    tileSize = size;
    ennemy = new QGraphicsPixmapItem(QPixmap(":/world_images/Xenemy.png").scaled(tileSize-5,tileSize+2), this);
    ennemy->setZValue(8);
    ennemy->setPos(x,y);
    ennemy->setVisible(true);

    deadennemy = new QGraphicsPixmapItem(QPixmap(":/world_images/deadXenemy.png").scaled(tileSize,tileSize), this);
    deadennemy->setZValue(8);
    deadennemy->setPos(x,y);
    deadennemy->setVisible(false);

    strenght= new QGraphicsTextItem(QString::number(value), this);
    strenght->setPos(x+tileSize/5,y-tileSize/1.5);
    strenght->setDefaultTextColor("red");
}

void XEnemyView::ondead()
{
    strenght->setVisible(false);
    ennemy->setVisible(false);
    deadennemy->setVisible(true);
}

void XEnemyView::updatepos(int x ,int y)
{
    strenght->setPos(x+tileSize/5,y-tileSize/1.5);
    ennemy->setPos(x,y);
    deadennemy->setPos(x,y);
}

