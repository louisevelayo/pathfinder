#ifndef MODELVIEW_H
#define MODELVIEW_H
#include <iostream>
#include "Model.h"
#include "qgraphicsview.h"
#include "protagonistview.h"
#include "Xenemy.h"
#include "Xenemyview.h"
#include "potionview.h"
#include "pathfinding.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QTimer>

class Controller;

class ModelView : public QGraphicsScene
{

    Q_OBJECT;

public:
    ModelView(int tileSize, Model *model, QString filename, Controller *controller);

    void showMap(const Model *model);
    void showProtagonist(Controller *controller);
    void updateProtagonist();
    void updateDirection(int direction);

    void showMapSegment();
    void showGVMap(QString filename);
    int getXMin(int x_pro);
    int getXMax(int x_pro);
    int getYMin(int y_pro);
    int getYMax(int y_pro);
    QGraphicsScene *getScene() const;
    void setScene(QGraphicsScene *newScene);
    void zoom(QWheelEvent * event);
    void showPotions(const Model *model);
    void showPotions();
    void removeRectItem(Model *model, std::string type);

    void setUI(Ui::MainWindow *newUI);
    void showXEnemies();
    void showPoisonousTiles(const Model *model);
    void updateXenemies(Model *model);

    ProtagonistView *getProtagonist() const;
    void updatePotions(Model *model);
    void showNormalEnemies();
    void showPEnemies();
    ProtagonistView *getProtagonist();

    int getTileSize() const;

    void drawPath(std::vector<TileStruct> path);
    void clearPath(std::vector<TileStruct> path);


    void attack();
    const std::vector<potiontileView *> &getPotionviews() const;

private:
    ProtagonistView *Prot;
    std::vector<bool> isDrawn;
    int tileSize;
    int maxRow;
    int maxCol;
    Model *model;
    std::vector<XEnemyView*> xenemieviews;
    std::vector<QGraphicsRectItem*> pathviews;
    std::vector<potiontileView*> potionviews;

};

#endif // MODELVIEW_H
