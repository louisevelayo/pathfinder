#include "penemyview.h"

PenemyView::PenemyView(int size, int x , int y , int poisonlevel, int value)
{
    tileSize = size;
    maxpoison= (poisonlevel);
    enemy = new QGraphicsPixmapItem(QPixmap(":/world_images/penemy.png").scaled(tileSize-8,tileSize-4), this);
    enemy->setZValue(8);
    enemy->setPos(x,y);
    enemy->setVisible(true);
    green=0;


    deadenemy = new QGraphicsPixmapItem(QPixmap(":/world_images/deadPenemy1.png").scaled(tileSize,tileSize), this);
    deadenemy->setZValue(8);
    deadenemy->setPos(x,y);
    deadenemy->setVisible(false);

    strenght= new QGraphicsTextItem(QString::number(value), this);
    strenght->setPos(x+tileSize/5,y-tileSize/1.5);
    strenght->setDefaultTextColor("purple");

    poison.clear();
    for(int r=-1; r<2; r++){
        for (int i=-1; i<2; i++){
            QGraphicsRectItem* poisonou = new QGraphicsRectItem(x+i*tileSize,y+r*tileSize, tileSize, tileSize, this);
            poisonou->setBrush(QColor(255, 0,0, maxpoison));
            poisonou->setPen(QColor(255, 0,0, maxpoison));
            poisonou->setZValue(7);
            poisonou->setVisible(false);
            poison.push_back(poisonou);
        }
    }
}



void PenemyView::ondead(){
      strenght->setVisible(false);
      enemy->setVisible(false);
      deadenemy->setVisible(true);
      for(int r=0; r<9; r++){
          poison[r]->setVisible(true);
      }
}

void PenemyView::onpoisonchange(int value)
{
    green+=value;
    for(int r=0; r<9; r++){
        poison[r]->setBrush(QColor(255, 0,0, maxpoison-green));
        poison[r]->setPen(QColor(255, 0, 0, maxpoison-green));
    }
}
