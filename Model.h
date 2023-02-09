#ifndef MODEL_H
#define MODEL_H
#include "world.h"
#include <QApplication>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <vector>
#include "poisonoustile.h"



class Model
{
private:
    std::vector<std::shared_ptr<Tile>> grid;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::shared_ptr<Protagonist> pikachu;
    std::vector<std::shared_ptr<Tile>> healthpacks;
    std::vector<std::shared_ptr<poisonousTile>> poisonousTiles;
    int rows;
    int col;
    World* world;

public:
    Model()= default;
    Model(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthpacks, float pRatio = 0.25f, float xRatio = 0.25);


    Protagonist*getPikachu() const;
    const std::vector<std::shared_ptr<Tile> > &getHealthpacks() const;
    const std::vector<std::shared_ptr<Enemy> > &getEnemies() const;
    const std::vector<std::shared_ptr<Tile> > &getGrid() const;


    void makeGridshared();
    void makeEnemyshared();
    void makeHealthpackshared();

    void createXenemy(float xratio);

    int getCol() const;
    int getRows() const;
    void getTileSquare(int x, int y, int weight);
    const std::vector<std::shared_ptr<poisonousTile> > &getPoisonousTiles() const;
    void updatePoisonousTiles();
    int typeEnemy(int i);
    void updatePoisonTilesaround(int x, int y, int strenght);

};

#endif // MODEL_H
