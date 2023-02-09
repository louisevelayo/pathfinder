#include "textscene.h"
#include "qgraphicsscene.h"
#include <QWidget>
#include <QChar>
#include "controller.h"

TextScene::TextScene(Controller *controller,Model *model): QGraphicsScene(){
    this->model = model;
    text = std::make_unique<QGraphicsTextItem>();
    this->controller = controller;
    this->rowsFull = model->getRows();
    this->colFull = model->getCol();
    writeMapSegment();
    updateWalls();
    showPotionsSegment();
    showEnemiesSegment();
    moveSegment();
}


void TextScene::writeMapSegment(){

    rows = 20;
    col = 20;
    Map = QString("");
    QTextStream stream(&Map);
    for(int j =0; j< col; j++){
        for(int i = 0; i<rows; i++){
            stream << "+---";

        }
        stream << "+\r\n";

        for(int i = 0; i<rows; i++){
            stream <<"|   ";
        }
    stream << "|\r\n";
    }
    for(int i = 0; i<rows; i++){
        stream << "+---";
    }
    stream << "+\r\n";

    Map = stream.readAll();
    text->setPlainText(Map);
    this->addItem(text.get());
    QFont font("New Courier");
    font.setStyleHint(QFont::Monospace);
    text->setFont(font);
}

void TextScene::updateMap(){
    for(int i=0; i<col; i++){
        for(int j=0; j<rows; j++){
            int index = i*4 + 2 +(2*j+1)*(4*col +3);
            Map[index] = QChar(' ');
        }
    }
}



void TextScene::moveSegment(){
    int x = model->getPikachu()->getXPos();
    int y = model->getPikachu()->getYPos();
    int updated;
    int xTemp = focusXPro(x);
    int yTemp = focusYPro(y);

    updated = xTemp*4 +2 + (2*yTemp+1)*(4*col +3);
    updateMap();
    updateWalls();
    showPotionsSegment();
    showEnemiesSegment();
    updatePoison();
    Map[updated] = QChar('G');
    text->setPlainText(Map);

}

void TextScene::updatePoison()
{
    int x = model->getPikachu()->getXPos();
    int y = model->getPikachu()->getYPos();
    QChar poisonText = '~';

    int xUp = focusXItem(x);
    int yUp = focusYItem(y);

    for(int i = 0; i < model->getPoisonousTiles().size();i++){
        int x = model->getPoisonousTiles()[i]->getXPos();
        int y = model->getPoisonousTiles()[i]->getYPos();
        if((xUp-rows/2 -1< x) && (x < rows/2+xUp) && (yUp - col/2 -1 < y) && (y < col/2 + yUp)){
            int xeq = (x + rows/2 -xUp)*4 + 2;
            int yeq = (2*(y+col/2-yUp)+1)*(4*col + 3);
            int index = xeq + yeq;
            if(model->getPoisonousTiles()[i]->getValue() < 10){
                poisonText = ' ';
            }
            Map[index] = poisonText;
        }
    }
}

void TextScene::showPotionsSegment(){
    int x = model->getPikachu()->getXPos();
    int y = model->getPikachu()->getYPos();

    int xUp = focusXItem(x);
    int yUp = focusYItem(y);

    for(int i = 0; i< model->getHealthpacks().size() ; i++){
        int x = model->getHealthpacks()[i]->getXPos();
        int y = model->getHealthpacks()[i]->getYPos();
        int drinked = controller->getModelView()->getPotionviews()[i]->getDrinked();
        QChar potionText = 'H';

        if((xUp-rows/2 -1< x) && (x < rows/2+xUp) && (yUp - col/2 -1 < y) && (y < col/2 + yUp)){
            int xeq = (x + rows/2 -xUp)*4 + 2;
            int yeq = (2*(y+col/2-yUp)+1)*(4*col + 3);
            int index = xeq + yeq;
            if(drinked == 1){
                potionText=  potionText.toLower();
            }
            Map[index] = QChar(potionText);
        }
    }
}

void TextScene::showEnemiesSegment() {
    int x = model->getPikachu()->getXPos();
    int y = model->getPikachu()->getYPos();

    int xUp = focusXItem(x);
    int yUp = focusYItem(y);


    for(int i = 0; i< model->getEnemies().size() ; i++){
            int x = model->getEnemies()[i]->getXPos();
            int y = model->getEnemies()[i]->getYPos();
            bool defeated = model->getEnemies()[i]->getDefeated();
            QChar enemyText;

            if((xUp-rows/2 -1< x) && (x < rows/2+xUp) && (yUp - col/2 -1 < y) && (y < col/2 + yUp)){
                int xeq = (x + rows/2 -xUp)*4 + 2;
                int yeq = (2*(y+col/2-yUp)+1)*(4*col + 3);
                int index = xeq + yeq;
                if(model->typeEnemy(i) == 2){                    
                    enemyText = 'X';
                }
                else if(model->typeEnemy(i) == 1){
                    enemyText = 'P';
                }
                else{
                    enemyText = 'E';
                }
                if(defeated == 1){
                    enemyText = enemyText.toLower();
                }
                Map[index] = QChar(enemyText);
            }
    text->setPlainText(Map);
    }

}

void TextScene::moveX(int x, int y, int direction){
    int xPro = model->getPikachu()->getXPos();
    int yPro = model->getPikachu()->getYPos();
    int old;


    int xUp = focusXItem(xPro);
    int yUp = focusYItem(yPro);

    if((xUp-rows/2+ 1< x) && (x < rows/2+xUp-1) && (yUp - col/2 +1 < y) && (y < col/2 + yUp -1)){
        int xeq = (x + rows/2 -xUp)*4 + 2;
        int yeq = (2*(y+col/2-yUp)+1)*(4*col + 3);
        int index = xeq + yeq;
        if(direction == 1){//right
            old = (x +rows/2 -xUp -1)*4 +2 + yeq;
        }
        else if(direction == 2){//left
            old = (x +rows/2 -xUp +1)*4 +2 +yeq;
        }
        else if(direction == 3){//down
            old = xeq +(2*(y+col/2-yUp-1)+1)*(4*col + 3);
        }
        else if(direction == 0){//up
            old = xeq +(2*(y+col/2-yUp+1)+1)*(4*col + 3);
        }
        Map[old] = QChar(' ');
        Map[index] = QChar('X');
        updatePoison();
        moveSegment();
        text->setPlainText(Map);
    }
}

void TextScene::updateWalls()
{
    int x = model->getPikachu()->getXPos();
    int y = model->getPikachu()->getYPos();
    int xUp = focusXItem(x);
    int yUp = focusYItem(y);


    for(int i = 0; i <model->getGrid().size(); i++){
        int x = model->getGrid()[i]->getXPos();
        int y = model->getGrid()[i]->getYPos();

        if((xUp-rows/2 -1< x) && (x < rows/2+xUp) && (yUp - col/2 -1 < y) && (y < col/2 + yUp)){
            if(model->getGrid()[i]->getValue()>1){
                int xeq = (x + rows/2 -xUp)*4 + 2;
                int yeq = (2*(y+col/2-yUp)+1)*(4*col + 3);
                int index = xeq + yeq;
                Map[index] = QChar('#');
            }
        }
    }
}

int TextScene::focusXPro(int x){
    if(x>rowsFull - rows/2){
        std::cout << "I'm here" << std::endl;
        return rows + x - rowsFull;}
    else if(x>rows/2){return rows/2;}
    else{return x;}
}

int TextScene::focusYPro(int y){
    if(y> colFull - col/2){return col + y -colFull;}
    else if(y>col/2){return col/2;}
    else{return y;}
}

int TextScene::focusXItem(int x)
{
    if(x > rowsFull - rows/2){return rowsFull - rows/2;}
    else if(x < rows/2){return rows/2;}
    else{return x;}
}

int TextScene::focusYItem(int y)
{
    if(y > colFull - col/2){return colFull -col/2;}
    else if(y < col/2){return col/2;}
    else{return y;}
}

void TextScene::setController(Controller *newController)
{
    controller = newController;
}


