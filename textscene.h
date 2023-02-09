#ifndef TEXTSCENE_H
#define TEXTSCENE_H
#include "Model.h"
#include "qgraphicsitem.h"
#include "qgraphicsscene.h"
#include <QTextEdit>
#include <QFile>

class Controller;
class TextScene: public QGraphicsScene
{
    Q_OBJECT
public:
    TextScene(Controller*,Model *model);
    void writeMapSegment();
    void updateMap();
    void showPotionsSegment();
    void showProtagonist();
    void showEnemiesSegment();
    void move(int direction);
    void moveSegment();
    void update();
    void updatePoison();
    void moveX(int, int, int);
    void updateWalls();

    int focusXPro(int);
    int focusYPro(int);

    int focusXItem(int);
    int focusYItem(int);

    void setController(Controller *newController);

    //void moveSegment(int direction);
private:
    QString gameMap;
    int rows;
    int rowsFull;

    int col;
    int colFull;
    Model *model;
    Controller *controller;
    std::unique_ptr<QGraphicsTextItem> text;
    QString Map;

public slots:


};

#endif // TEXTSCENE_H
