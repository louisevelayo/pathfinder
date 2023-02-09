#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <iostream>
#include "Model.h"
#include "mapview.h"
#include <QKeyEvent>
#include <iostream>
#include "modelview.h"
#include "textscene.h"
#include <cstdlib>
#include "pathfinding.h"
#include <QTimer>

class Controller: public QObject
{
public:
    Controller(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthpacks, float pRatio = 0.25f, float xRatio = 0.25f);

    float check(int posX, int posY); //checks what happens if they move a certain direction

    bool move(std::string direction);

    bool attackEnemy(int i);

    int checkEnemy(int posX, int posY);

    int checkPotion(int posX, int posY);
    void drinkPotion(int i);


    void printProtagonistPosition();
    void printProtagonistHealth();
    void printProtagonistEnergy();
    void printDimensions();
    void printMap();
    void printPositionEnemies();


    void win(); //Shows to the player that they have won
    void lose(); //Shows to the player that they have lost

    void printView();
    void printTextView();

    Model *getModel() const;

    void printEnemyType();
    ModelView *getModelView() const;

    void MoveXenemy();

    void printXenemy();
    void printType();

    int checkPoisonous(int posX, int posY);
    TextScene *getTextScene() const;
    void updatePoisonLevel();

    Pathfinding *getPathfinder() const;
    void drawPath(std::vector<TileStruct> path);
    void clearPath(std::vector<TileStruct> path);
    void findPath(int startX, int startY, int endX, int endY);




    int getClosestEnemy();
    int getClosestPotion();

    MapView *getMapView();

    void setauto();
    void setAutoplay(bool newAutoplay);

    bool getAutoplay();

public slots:
        void timeraction();
        void setWeight(float weight);
        void autoclicked();

private:
    QTimer *timer;
    Model *model;
    ModelView *modelView;
    MapView *mapView;
    Pathfinding *pathfinder;
    TextScene *textScene;
    bool firstClick;
    bool autoplay;

signals:


public slots:

private slots:


};

#endif // CONTROLLER_H
