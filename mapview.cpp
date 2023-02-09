#include "mapview.h"
#include "protagonistview.h"
#include <iostream>
#include <QWheelEvent>
#include "controller.h"



MapView::MapView(QWidget *parent) :QGraphicsView(parent)
{
    timer= new QTimer(this);
    timer->start(300);
    xT=0;
    yT=0;
    autoplay=false;
    connect(timer, &QTimer::timeout, this, &MapView::timeraction);

}

void MapView::keyPressEvent(QKeyEvent * event){
    qreal x_update;
    qreal y_update;
    int moved = 0;

    if(event->key() == Qt::Key_Left){
        if(controller->move("Left")){
            x_update = protagonist->x()-tileSize;
            y_update = protagonist->y();
            moved = 1;
        }
    }
    else if(event->key() == Qt::Key_Right){
        if(controller->move("Right")){
            x_update = protagonist->x()+tileSize;
            y_update = protagonist->y();
            moved = 1;
        }
    }
    else if(event->key() == Qt::Key_Up){
        if(controller->move("Up")){
            x_update = protagonist->x();
            y_update = protagonist->y()-tileSize;
            moved = 1;
        }
    }
    else if(event->key() == Qt::Key_Down){
        if(controller->move("Down")){
            x_update = protagonist->x();
            y_update = protagonist->y()+tileSize;
            moved = 1;
        }
    }
    if(moved == 1){
        protagonist->setPos(x_update,y_update);
        protagonist->setZValue(10);
        this->centerOn(protagonist);
    }
}

void MapView::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(AnchorUnderMouse);
    double scaleFactor = 1.15;

    if(event->angleDelta().y() > 0)
    {
        scale(scaleFactor,scaleFactor);
    }

    if(event->angleDelta().y() < 0)
    {
        scale(1/scaleFactor,1/scaleFactor);
    }
}



void MapView::setTileSize(int newTileSize)
{
    tileSize = newTileSize;
}

void MapView::setController(Controller *newController)
{
    controller = newController;
    setProtagonist(controller->getModelView()->getProtagonist());
    setTileSize(controller->getModelView()->getTileSize());
}

void MapView::setProtagonist(ProtagonistView *newProtagonist)
{
    protagonist = newProtagonist;
}

void MapView::mousePressEvent(QMouseEvent *event){
    /*
     * Only activate pathfinder if SHIFT is pressed
     */
    if (event->modifiers() & Qt::ShiftModifier) {
        auto mapped = mapToScene(event->pos());
        auto x{mapped.x()}, y{mapped.y()};
        // Check whether click is legal -- Cant click outside the image
        if (x < 0 || y < 0){
            std::cout << "out of bounds" << std::endl;
            return;
        }

        // Check whether click is legal -- Cant click outside the image
        if (x > sceneRect().width() || y > sceneRect().height()){
            std::cout << "out of bounds" << std::endl;
            return;
        }
        xT = floor(x/30);
        yT = floor(y/30);


        std::cout <<"xT: "<<xT<< " yT: "<<yT << std::endl;
        usePathfind(xT,yT);
        activatepathfinder=true;
        } else{
            this->centerOn(protagonist);
            std::cout << "this is a click" << std::endl;
    }
}

void MapView::setActivatepathfinder(bool newActivatepathfinder)
{
    activatepathfinder = newActivatepathfinder;
}

void MapView::usePathfind(int x, int y){
    xT=x;
    yT=y;
    int rcStart = controller->getPathfinder()->setStartWithCoords(controller->getModel()->getPikachu()->getXPos(), controller->getModel()->getPikachu()->getYPos());

    if(rcStart == -1){
        std::cout << "Invalid start coordinates: pathfinding not started" << std::endl;
        return;
    }
    int rcTarget = controller->getPathfinder()->setTargetWithCoords(xT,yT);
    if(rcTarget == -1){
        std::cout << "Invalid target coordinates: pathfinding not started" << std::endl;
        return;
    }
    controller->getPathfinder()->findPath();
    controller->getModelView()->drawPath(controller->getPathfinder()->getPath());
}

void MapView::playauto(){
    if(controller->getAutoplay()==true){
        auto enemy= controller->getModel()->getEnemies()[controller->getClosestEnemy()];
        int enemyStrenght = enemy->getValue();
        if(enemyStrenght>=controller->getModel()->getPikachu()->getHealth()){
            auto potion = controller->getModel()->getHealthpacks()[controller->getClosestPotion()];
            usePathfind(potion->getXPos(), potion->getYPos());
        }
        else{
            usePathfind(enemy->getXPos(),enemy->getYPos());
        }
        activatepathfinder=true;
    }
}

void MapView::timeraction(){
    qreal x_update;
    qreal y_update;
    int moved = 0;
    if(!activatepathfinder){
        yT=controller->getModel()->getPikachu()->getYPos();
        xT=controller->getModel()->getPikachu()->getXPos();
    }
    if(((controller->getModel()->getPikachu()->getXPos()==xT)&&(controller->getModel()->getPikachu()->getYPos()==yT))){
        activatepathfinder = false;
        index=0;
        std::cout<<"the lil guy is here  "<<std::endl;
        playauto();

    }
    if(activatepathfinder==true){
            int ox =controller->getPathfinder()->getPath()[index].xCord;
            int oy =controller->getPathfinder()->getPath()[index].yCord;
            int currentx=controller->getModel()->getPikachu()->getXPos();
            int currenty=controller->getModel()->getPikachu()->getYPos();
            if((currentx>ox)&&(currenty==oy)){
                if(controller->move("Left")){
                    x_update = protagonist->x()-tileSize;
                    y_update = protagonist->y();
                    moved = 1;
                }
            }
            if((currentx<ox)&&(currenty==oy)){
                if(controller->move("Right")){
                    x_update = protagonist->x()+tileSize;
                    y_update = protagonist->y();
                    moved = 1;
                }
            }
            if((currentx==ox)&&(currenty>oy)){
                if(controller->move("Up")){
                    x_update = protagonist->x();
                    y_update = protagonist->y()-tileSize;
                    moved = 1;
                }
            }
            if((currentx==ox)&&(currenty<oy)){
                if(controller->move("Down")){
                    x_update = protagonist->x();
                    y_update = protagonist->y()+tileSize;
                    moved = 1;
                }
            }
            if(moved == 1){
                protagonist->setPos(x_update,y_update);
                protagonist->setZValue(10);
                this->centerOn(protagonist);
            }
            index++;
        }
}



