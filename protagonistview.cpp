#include "protagonistview.h"
#include <QKeyEvent>
#include <iostream>
#include "controller.h"
#include "modelview.h"


ProtagonistView::ProtagonistView(Controller *controllerTouse, int tileSize, int xpos, int ypos)
{
    controller= controllerTouse;
    this->tileSize = tileSize;

    frame1 = new QGraphicsPixmapItem(QPixmap(":/world_images/goomba.png").scaled(tileSize,tileSize), this);
    frame1->setZValue(9);
    frame1->setPos(xpos,ypos);
    frame1->setVisible(true);

    frame2 = new QGraphicsPixmapItem(QPixmap(":/world_images/goomba2.png").scaled(tileSize,tileSize), this);
    frame2->setZValue(9);
    frame2->setPos(xpos,ypos);
    frame2->setVisible(false);

    attack = new QGraphicsPixmapItem(QPixmap(":/world_images/sword.png").scaled(tileSize,tileSize), this);
    attack->setZValue(10);
    attack->setPos(xpos+tileSize/2,ypos-tileSize/2);
    attack->setVisible(true);

    attack2 = new QGraphicsPixmapItem(QPixmap(":/world_images/sword2.png").scaled(tileSize,tileSize), this);
    attack2->setZValue(10);
    attack2->setPos(xpos+tileSize/2,ypos+tileSize/2);
    attack2->setVisible(true);


    animationTimer=new QTimer(this);
    animationTimer->start(100);
    connect(animationTimer, &QTimer::timeout, this, &ProtagonistView::timeraction);
    timerbool=true;
    attackbool=0;
    iterations=0;
}

void ProtagonistView::timeraction(){
    if(iterations==3){
        frame1->setVisible(timerbool);
        frame2->setVisible(!timerbool);
        iterations=0;
    }
    iterations++;
    attackbool--;
    if(attackbool==2){
        attack->setVisible(true);
        attack2->setVisible(false);
    }
    if(attackbool==1){
        attack->setVisible(false);
        attack2->setVisible(true);
    }

    if(attackbool<=0){
        attack->setVisible(false);
        attack2->setVisible(false);
        attackbool=0;
    }
    timerbool=!timerbool;
}

void ProtagonistView::attackEnemy(){
    attackbool=3;
}
/*


void ProtagonistView::keyPressEvent(QKeyEvent * event){
    qreal x_update;
    qreal y_update;
    int moved = 0;

    if(event->key() == Qt::Key_Left){
        if(controller->move("Left")){
            x_update = x()-tileSize;
            y_update = y();
            moved = 1;

        }
    }
    else if(event->key() == Qt::Key_Right){
        if(controller->move("Right")){
            x_update = x()+tileSize;
            y_update = y();
            moved = 1;

        }
    }
    else if(event->key() == Qt::Key_Up){
        if(controller->move("Up")){
            x_update = x();
            y_update = y()-tileSize;
            moved = 1;
        }
    }
    else if(event->key() == Qt::Key_Down){
        if(controller->move("Down")){
            x_update = x();
            y_update = y()+tileSize;
            moved = 1;
        }
    }
    if(moved ==1){
        setPos(x_update,y_update);
        setZValue(10);
    }
}
*/

void ProtagonistView::updateWithPrompt(QString direction){
    qreal x_update;
    qreal y_update;

    if(direction == "left"){
        if(controller->move("Left")){
            x_update = x()-tileSize;
            y_update = y();

        }
    }
    else if(direction == "right"){
        if(controller->move("Right")){
            x_update = x()+tileSize;
            y_update = y();
        }
    }
    else if(direction == "up"){
        if(controller->move("Up")){
            x_update = x();
            y_update = y()-tileSize;

        }
    }
    else if(direction == "down"){
        if(controller->move("Down")){
            x_update = x();
            y_update = y()+tileSize;

        }
    }
    setPos(x_update,y_update);
    setZValue(10);

}

void ProtagonistView::onPosChanged(int x, int y)
{
    frame1->setPos(x,y);
    frame2->setPos(x,y);

}
