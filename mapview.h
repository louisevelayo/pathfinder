#ifndef MAPVIEW_H
#define MAPVIEW_H

#include "protagonistview.h"
#include <QGraphicsView>
#include <QtWidgets>
#include <QWidget>
#include <QWheelEvent>
#include <QTimer>

class Controller;

class MapView: public QGraphicsView
{
    Q_OBJECT
public:
    explicit MapView(QWidget *parent = 0);
    MapView(Controller *controller);

    void setProtagonist(ProtagonistView *newProtagonist);

    void setController(Controller *newController);

    void setTileSize(int newTileSize);

    void usePathfind(int x, int y);
    void playauto();

    void activateAuto(bool value);
    void setActivatepathfinder(bool newActivatepathfinder);

public slots:
    void timeraction();
protected:
    void keyPressEvent(QKeyEvent * event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *ev) override;
private:
    ProtagonistView * protagonist;
    Controller * controller;
    int tileSize;
    int xT;
    int yT;
    int index;
    QTimer* timer;
    bool activatepathfinder;
    bool autoplay;

};


#endif // MAPVIEW_H
