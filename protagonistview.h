#ifndef PROTAGONISTVIEW_H
#define PROTAGONISTVIEW_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <Model.h>
#include <QTimer>

class Controller;

class ProtagonistView: public QGraphicsPixmapItem, public QObject
{
public:
    ProtagonistView(Controller *controllerTouse, int tileSize, int xPosition, int yPosition);
    //void keyPressEvent(QKeyEvent * event);
    void updateWithPrompt(QString direction);

    void attackEnemy();
public slots:
    void timeraction();
    void onPosChanged(int x, int y);
private:
    Controller *controller;
    int tileSize;
    QGraphicsPixmapItem *frame1, *frame2, *attack, *attack2;
    QTimer *animationTimer;
    bool timerbool;
    int attackbool;
    int iterations;

};
#endif // PROTAGONISTVIEW_H
