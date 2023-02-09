#include "modelview.h"
#include "Xenemy.h"
#include "normalennemyview.h"
#include "qevent.h"
#include "controller.h"
#include <QPixmap>
#include <QWheelEvent>
#include "poisonoustile.h"
#include "poisonoustileview.h"
#include "penemyview.h"
#include <QGraphicsPixmapItem>

ModelView::ModelView(int tileSize, Model *model, QString filename, Controller * controller): QGraphicsScene(){
    this->model = model;
    this->tileSize = tileSize;
    this->maxRow = model->getRows();
    this->maxCol = model->getCol();

    showGVMap(filename);

}

void ModelView::attack(){
    Prot->attackEnemy();
}


int ModelView::getXMin(int x_pro){
    if (x_pro -100 < 0 ){
        return 0;
    }
    else{return x_pro -100;}
}

int ModelView::getXMax(int x_pro){
    if (x_pro +100 > maxCol){
        return maxCol;
    }
    else{return x_pro +100;}
}

int ModelView::getYMin(int y_pro){
    if (y_pro -100 < 0 ){
        return 0;
    }
    else{return y_pro -100;}
}

int ModelView::getYMax(int y_pro){
    if (y_pro +100 > maxRow){
        return maxRow;
    }
    else{return y_pro +100;}
}



void ModelView::showMap(const Model *model)
{
    for(int i = 0; i< model->getGrid().size() ; i++){
        int x = model->getGrid()[i]->getXPos()*tileSize;
        int y = model->getGrid()[i]->getYPos()*tileSize;

        QGraphicsRectItem * tile = this->addRect(x,y,tileSize,tileSize);
        tile->setBrush(QColor(model->getGrid()[i]->getValue()*255, 98,200));
        tile->setPen(QColor(model->getGrid()[i]->getValue()*255, 98, 200));
    }
}

void ModelView::showGVMap(QString filename)
{
    QPixmap map(filename);
    QGraphicsPixmapItem * GVmap = new QGraphicsPixmapItem(map);
    GVmap->setPixmap(map);
    GVmap->setFlag(QGraphicsItem::ItemIsFocusable,false);
    GVmap->setScale(tileSize);
    this->addItem(GVmap);

}

void ModelView::updateDirection(int direction){
    int xPi = model->getPikachu()->getXPos();
    int yPi = model->getPikachu()->getYPos();

    int xMin = getXMin(xPi);
    int xMax = getXMax(xPi);
    int yMin = getYMin(yPi);
    int yMax = getYMax(yPi);

    if(direction == 0){//left
        int xUpdate = xMin + 1;
        for(int y = yMin; y < yMax; y++){
            if(isDrawn[xUpdate + y*model->getCol()] == false){
                 QGraphicsRectItem * tile= this->addRect(xUpdate*tileSize,y*tileSize,tileSize,tileSize);
                 tile->setFlag(QGraphicsItem::ItemIsFocusable,false);
                 tile->setBrush(QColor(model->getGrid()[xUpdate + y*model->getCol()]->getValue()*255, 98,200));
                 tile->setPen(QColor(model->getGrid()[xUpdate + y*model->getCol()]->getValue()*255, 98, 200));
                 isDrawn[xUpdate + y*model->getCol()] = true;
            }
        }
    }

    if(direction == 1){//up
      int yUpdate = yMin + 1;
      for(int x = xMin; x<xMax; x++){
          if(isDrawn[x + yUpdate*model->getCol()] == false){
              QGraphicsRectItem * tile= this->addRect(x*tileSize,yUpdate*tileSize,tileSize,tileSize);
              tile->setFlag(QGraphicsItem::ItemIsFocusable,false);
              tile->setBrush(QColor(model->getGrid()[x + yUpdate*model->getCol()]->getValue()*255, 98,200));
              tile->setPen(QColor(model->getGrid()[x + yUpdate*model->getCol()]->getValue()*255, 98, 200));
              isDrawn[x + yUpdate*model->getCol()] = true;
          }
      }
    }

    if(direction == 2){//right
        int xUpdate = xMax -1;
        for(int y = yMin; y < yMax; y++){
            if(isDrawn[xUpdate + y*model->getCol()] == false){
                QGraphicsRectItem * tile= this->addRect(xUpdate*tileSize,y*tileSize,tileSize,tileSize);
                tile->setFlag(QGraphicsItem::ItemIsFocusable,false);
                tile->setBrush(QColor(model->getGrid()[xUpdate + y*model->getCol()]->getValue()*255, 98,200));
                tile->setPen(QColor(model->getGrid()[xUpdate + y*model->getCol()]->getValue()*255, 98, 200));
                isDrawn[xUpdate + y*model->getCol()] = true;

            }
        }
    }
    if(direction == 3){//down
      int yUpdate = yMax -1;
      for(int x = xMin; x<xMax; x++){
          if(isDrawn[x + yUpdate*model->getCol()] == false){
              QGraphicsRectItem * tile= this->addRect(x*tileSize,yUpdate*tileSize,tileSize,tileSize);
              tile->setFlag(QGraphicsItem::ItemIsFocusable,false);
              tile->setBrush(QColor(model->getGrid()[x + yUpdate*model->getCol()]->getValue()*255, 98,200));
              tile->setPen(QColor(model->getGrid()[x + yUpdate*model->getCol()]->getValue()*255, 98, 200));
              isDrawn[x + yUpdate*model->getCol()] = true;
          }
      }
    }
}

void ModelView::showProtagonist(Controller *controller)
{
    Prot = new ProtagonistView(controller,tileSize, model->getPikachu()->getXPos()*tileSize, model->getPikachu()->getYPos()*tileSize);
    //Prot->setPixmap(QPixmap(":/world_images/goomba.png").scaled(tileSize,tileSize));
    Prot->setFlag(QGraphicsItem::ItemIsFocusable);
    Prot->setFocus();
    this->addItem(Prot);
    //connect(&(*model->getPikachu()), &Protagonist::posChanged, Prot, &ProtagonistView::onPosChanged);
}


void ModelView::showPotions(){
    for(int i = 0; i< model->getHealthpacks().size() ; i++){
            int x = model->getHealthpacks()[i]->getXPos()*tileSize;
            int y = model->getHealthpacks()[i]->getYPos()*tileSize;
            potiontileView * potion= new potiontileView( tileSize, x, y);
            this->addItem(potion);

            potionviews.push_back(potion);
    }
}

void ModelView::showXEnemies(){
    for(int i = 0; i< model->getEnemies().size() ; i++){
            auto enemyfrommodel = model->getEnemies()[i];
            int x = enemyfrommodel->getXPos()*tileSize;
            int y = enemyfrommodel->getYPos()*tileSize;
            if(model->typeEnemy(i)==2){
                auto xenemy = std::dynamic_pointer_cast<Xenemy>(model->getEnemies()[i]);
                auto enemyx= new XEnemyView(tileSize, x, y, xenemy->getValue());
                this->addItem(enemyx);
                xenemieviews.push_back(enemyx);
                connect(&(*xenemy), &Xenemy::dead, enemyx, &XEnemyView::ondead);
            }
    }
}

void ModelView::showNormalEnemies(){
    for(int i = 0; i< model->getEnemies().size() ; i++){
        auto enemyfrommodel = model->getEnemies()[i];
        int x = enemyfrommodel->getXPos()*tileSize;
        int y = enemyfrommodel->getYPos()*tileSize;
        if(model->typeEnemy(i)==0){
            auto enemy= new normalEnnemyView(tileSize, x, y, enemyfrommodel->getValue());
            this->addItem(enemy);
            connect(&(*enemyfrommodel), &Enemy::dead, enemy, &normalEnnemyView::ondead);
        }
    }
}

void ModelView::showPEnemies(){
    for(int i = 0; i< model->getEnemies().size() ; i++){
            auto enemyfrommodel = model->getEnemies()[i];
            int x = enemyfrommodel->getXPos()*tileSize;
            int y = enemyfrommodel->getYPos()*tileSize;
            if(model->typeEnemy(i)==1){
                auto penemy = std::dynamic_pointer_cast<PEnemy>(model->getEnemies()[i]);
                auto enemyp= new PenemyView(tileSize, x, y, penemy->getPoisonLevel(), enemyfrommodel->getValue());
                this->addItem(enemyp);
                connect(&(*penemy), &PEnemy::dead, enemyp, &PenemyView::ondead);
                connect(&(*penemy), &PEnemy::poisonLevelUpdated, enemyp, &PenemyView::onpoisonchange);
            }
    }
}

void ModelView::updateXenemies(Model *model){
    int index=0;
    for(int i = 0; i< model->getEnemies().size() ; i++){
        if(model->typeEnemy(i)==2){
            int x = model->getEnemies()[i]->getXPos()*tileSize;
            int y = model->getEnemies()[i]->getYPos()*tileSize;
            xenemieviews[index]->updatepos(x, y);
            index++;
        }
    }
}

void ModelView::updatePotions(Model *model){
    int index=0;
    for(int i = 0; i< model->getHealthpacks().size() ; i++){
        if(model->getHealthpacks()[i]->getValue()<1){
            potionviews[i]->updatedrinked();
            index++;
        }
    }
}
ProtagonistView *ModelView::getProtagonist()
{
    return Prot;
}


int ModelView::getTileSize() const
{
    return tileSize;
}

void ModelView::drawPath(std::vector<TileStruct> path)
{

    for(auto t : pathviews){
        t->setVisible(false);
    }
    pathviews.clear();
    for(auto t : path){
        int xCord = t.xCord;
        int yCord = t.yCord;

        QGraphicsRectItem * tileInPath = this->addRect(xCord*tileSize,yCord*tileSize,tileSize,tileSize);
        tileInPath->setBrush(QColor("red"));
        tileInPath->setOpacity(0.4);
        pathviews.push_back(tileInPath);
        tileInPath->setZValue(0);
    }
}

const std::vector<potiontileView *> &ModelView::getPotionviews() const
{
    return potionviews;
}


//void ModelView::zoom(QWheelEvent * event){
//    std::cout << "line 182" << std::endl;
//    if(event->angleDelta().manhattanLength() < 0 ){
//        UI->graphicsView->scale(1.1,1.1);
//    }
//}


//void ModelView::showMapSegment(){
//    int xPi = model->getPikachu()->getXPos();
//    int yPi = model->getPikachu()->getYPos();

//    int xMin = getXMin(xPi);
//    int xMax = getXMax(xPi);
//    int yMin = getYMin(yPi);
//    int yMax = getYMax(yPi);

//    for(int x = xMin; x < xMax; x++){
//        for (int y = yMin; y< yMax ; y++){
//            int index = x + y*model->getCol();
//            QGraphicsRectItem * tile= scene->addRect(x*tileSize,y*tileSize,tileSize,tileSize);
//            tile->setBrush(QColor(model->getGrid()[index]->getValue()*255));
//            tile->setPen(QColor(model->getGrid()[index]->getValue()*255));
//        }
//    }
//}

//void ModelView::showPoisonousTiles(const Model *model){
//    for(int i = 0 ; i<model->getPoisonousTiles().size(); i++){
//        std::shared_ptr<poisonousTile> poisontile = model->getPoisonousTiles()[i];
//        int x = poisontile->getXPos()*tileSize;
//        int y = poisontile->getYPos()*tileSize;
//        auto tile= new poisonTileView(tileSize, x, y);
//        scene->addItem(tile);
//        connect(&(*poisontile), &poisonousTile::isactivated, tile, &poisonTileView::show);
//    }
//}
