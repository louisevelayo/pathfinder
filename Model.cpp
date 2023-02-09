#include "Model.h"
#include "Xenemy.h"
#include <vector>
#include "poisonoustile.h"

int Model::getRows() const
{
    return rows;
}

int Model::getCol() const
{
    return col;
}

const std::vector<std::shared_ptr<poisonousTile> > &Model::getPoisonousTiles() const
{
    return poisonousTiles;
}

Model::Model(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthpacks, float pRatio, float Xratio)
{
    this->world = new World();
    world->createWorld(filename, nrOfEnemies, nrOfHealthpacks, pRatio);
    this->col = world->getCols();
    this->rows = world->getRows();
    this->pikachu = world->getProtagonist();
    makeEnemyshared();
    makeHealthpackshared();
    makeGridshared();
    createXenemy(Xratio);
}

int Model::typeEnemy(int i){
    auto xenemy = std::dynamic_pointer_cast<Xenemy>(getEnemies()[i]);
    auto penemy = std::dynamic_pointer_cast<PEnemy>(getEnemies()[i]);
    if(xenemy!=nullptr){
        return 2;
    }
    if(penemy!=nullptr){
        return 1;
    }
    else{
        return 0;
    }
}

void Model::getTileSquare(int x, int y, int weight){
    std::vector<std::shared_ptr<poisonousTile>> square;
    for(int r=-1; r<2; r++){
        for (int i=-1; i<2; i++){
            std::shared_ptr<poisonousTile> poisonous = std::make_shared<poisonousTile>(x+i, y+r, weight);
            std::cout<<"the weight of the tile is: "<<weight<<std::endl;
            poisonousTiles.push_back(poisonous);
        }
    }
}

void Model::updatePoisonousTiles(){
    for(auto &tile : poisonousTiles){
        tile->setValue(tile->getValue()-rand()%100);
    }
}

void Model::updatePoisonTilesaround(int x, int y, int strenght){
    if(getPoisonousTiles().size()==0){
//        std::cout<<"no tiles anymore"<<std::endl;
    }
    else{
        for(int i=0; i<getPoisonousTiles().size(); i++){
            if((getPoisonousTiles()[i]->getXPos()==x)&&(getPoisonousTiles()[i]->getYPos()==y)){
                for(int p=i-4; p<i+5;p++){
                    getPoisonousTiles()[p]->setValue(getPoisonousTiles()[p]->getValue()-strenght);

                    if(getPoisonousTiles()[p]->getValue()<0){
                        poisonousTiles[p]->setValue(0);
                    }
                }
            }
        }
    }
}

void Model::createXenemy(float xratio){
    int max_xenemy = xratio*enemies.size();
    int num = 0;
    for(int i=0; i<enemies.size(); i++){
        auto penemy =std::dynamic_pointer_cast<PEnemy>(enemies[i]);
        if(penemy == nullptr){
            if(num<= max_xenemy){
                  std::shared_ptr<Xenemy> xenemy = std::make_shared<Xenemy>(enemies[i]->getXPos(), enemies[i]->getYPos(), enemies[i]->getValue());
                  enemies.erase(enemies.begin()+(i));
                  enemies.push_back(xenemy);
                  num++;
                  std::cout<<"x enemy added"<<std::endl;
            }
        }
    }
}




Protagonist*Model::getPikachu() const
{
    return pikachu.get();
}

const std::vector<std::shared_ptr<Tile>> &Model::getGrid() const
{
    return grid;
}

void Model::makeGridshared()
{
    for(auto &tile : world->getTiles()){
            std::shared_ptr<Tile> newTile = std::move(tile);
            grid.push_back(newTile);
        }

}

void Model::makeEnemyshared()
{
    for(auto &enemy : world->getEnemies()){
        std::shared_ptr<Enemy> newEnemy = std::move(enemy);
        enemies.push_back( newEnemy );
    }
}

void Model::makeHealthpackshared()
{
    for(auto &Health : world->getHealthPacks()){
        std::shared_ptr<Tile> newHealth = std::move(Health);
        healthpacks.push_back(newHealth);
    }
}


const std::vector<std::shared_ptr<Tile> > &Model::getHealthpacks() const
{
    return healthpacks;
}

const std::vector<std::shared_ptr<Enemy> > &Model::getEnemies() const
{
    return enemies;
}
