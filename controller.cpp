#include "controller.h"
#include "Xenemy.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <Model.h>

void move(std::string direction); //move in "direction"

void Controller::lose(){
    std::cout << "You have lost!" << std::endl;
    model->getPikachu()->setEnergy(0);
    model->getPikachu()->setHealth(0);
}

void Controller::setWeight(float weight){
    pathfinder->setWeight(weight/100);
}

void Controller::autoclicked()
{
    autoplay = !autoplay;
}

bool Controller::getAutoplay(){
    return autoplay;
}

void Controller::setAutoplay(bool newAutoplay)
{
    autoplay = newAutoplay;
}

Controller::Controller(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthpacks, float pRatio, float xRatio)
{
    this->model =  new Model(filename, nrOfEnemies, nrOfHealthpacks, pRatio, xRatio);
    this->modelView = new ModelView(30, model, filename, this);
    this->pathfinder = new Pathfinding();
    modelView->showGVMap(filename);
    model->getPikachu()->setEnergy(100);
    pathfinder->setModel(this->model);
    pathfinder->setup();
    pathfinder->setWeight(0);
    timer= new QTimer(this);
    timer->start(1000);
    connect(timer, &QTimer::timeout, this, &Controller::timeraction);
    model->getPikachu()->setXPos(0);
    model->getPikachu()->setYPos(0);
    while((check(model->getPikachu()->getXPos(), model->getPikachu()->getYPos())==-1)||(check(model->getPikachu()->getXPos(), model->getPikachu()->getYPos())>1)||(check(model->getPikachu()->getXPos(), model->getPikachu()->getYPos())<0)){
        model->getPikachu()->setXPos(model->getPikachu()->getXPos()+1);
        model->getPikachu()->setYPos(model->getPikachu()->getYPos()+1);
    }
    modelView->showProtagonist(this);
    modelView->showPotions();
    modelView->showXEnemies();
    modelView->showPEnemies();
    modelView->showNormalEnemies();
    this->textScene = new TextScene(this,model);
}

float Controller::check(int posX, int posY)
{
    if((posX>=0)&&(posX<model->getCol())&&(posY>=0)&&(posY<model->getRows())){
        return 1-model->getGrid()[posY*model->getCol()+posX]->getValue();
    }
    else{
        return -1;
    }
}

int Controller::checkPoisonous(int posX, int posY){
    for(int i = 0 ; i<model->getPoisonousTiles().size(); i++){
        if((model->getPoisonousTiles()[i]->getXPos()==posX)&&(model->getPoisonousTiles()[i]->getYPos()==posY)){
            return i;
        }
    }
    return -1;
}

TextScene *Controller::getTextScene() const{
    return textScene;
}
void Controller::timeraction()
{
    MoveXenemy();
    updatePoisonLevel();
}


Pathfinding *Controller::getPathfinder() const
{
    return pathfinder;
}


void Controller::updatePoisonLevel(){
    for(int i=0; i<model->getEnemies().size(); i++){
        if((model->typeEnemy(i)==1)&&(model->getEnemies()[i]->getDefeated())){
            auto penemy = std::dynamic_pointer_cast<PEnemy>(model->getEnemies()[i]);
            int newpoisonlevel= rand()%50;
            penemy->setPoisonLevel(penemy->getPoisonLevel()-newpoisonlevel);
            penemy-> emit poisonLevelUpdated(newpoisonlevel);
            std::cout << "poison level: " <<newpoisonlevel << std::endl;
            model->updatePoisonTilesaround(penemy->getXPos(), penemy->getYPos(), newpoisonlevel);
        }
    }
}

bool Controller::attackEnemy(int i){
    std::cout<<"before attack life :"<<model->getPikachu()->getHealth()<<" health of enemy:"<< model->getEnemies()[i]->getValue()<<std::endl;
    if(model->getPikachu()->getHealth()>model->getEnemies()[i]->getValue()){
        model->getPikachu()->setHealth(model->getPikachu()->getHealth()-(model->getEnemies()[i]->getValue()));
        model->getEnemies()[i]->setValue(0);
        if((model->typeEnemy(i)==1)&&(model->getEnemies()[i]->getDefeated()==false)){
            auto penemy = std::dynamic_pointer_cast<PEnemy>(model->getEnemies()[i]);
            model->getTileSquare(penemy->getXPos(), penemy->getYPos(), penemy->getPoisonLevel());
        }
        model->getEnemies()[i]->setDefeated(true);
        model->getEnemies()[i]-> emit dead();
        model->getPikachu()->setEnergy(100);
        modelView->attack();
        std::cout<<"after attack life: "<<model->getPikachu()->getHealth()<<" health of enemy:"<< model->getEnemies()[i]->getValue()<<std::endl;
    }
    else{
        lose();
    }
}

int Controller::getClosestEnemy(){
    int indexclosest=0;
    double closestdistance= 100000;
    for(int i=0; i<(int) model->getEnemies().size(); i++){
        int distancex= (model->getEnemies()[i]->getXPos()-(model->getPikachu()->getXPos()));
        int distancey= (model->getEnemies()[i]->getYPos()-(model->getPikachu()->getYPos()));
        double distance= sqrt((distancex*distancex)+(distancey*distancey));
        if((distance<closestdistance)&&(model->getEnemies()[i]->getValue()>0)&&(model->typeEnemy(i)!=2)){
            closestdistance=distance;
            indexclosest=i;
        }
    }
    std::cout<<"closest enemy x: "<<model->getEnemies()[indexclosest]->getXPos()<<" y:"<< model->getEnemies()[indexclosest]->getYPos()<<std::endl;
    return indexclosest;
}

int Controller::getClosestPotion(){
    int indexclosest=0;
    double closestdistance=10000;
    for(int i=0; i<(int) model->getHealthpacks().size(); i++){
        int distancex= (model->getHealthpacks()[i]->getXPos()-(model->getPikachu()->getXPos()));
        int distancey= (model->getHealthpacks()[i]->getYPos()-(model->getPikachu()->getYPos()));
        double distance= sqrt((distancex*distancex)+(distancey*distancey));
        if((distance<closestdistance)&&(model->getHealthpacks()[i]->getValue()>0)){
            closestdistance=distance;
            indexclosest=i;
        }
    }
    return indexclosest;
}


int Controller::checkEnemy(int posX, int posY){
    for(int i=0; i<model->getEnemies().size(); i++){
        if((model->getEnemies()[i]->getXPos()==posX)&&((model->getEnemies()[i]->getYPos()==posY))){
            return i;
        }
    }
    return -1;
}

int Controller::checkPotion(int posX, int posY){
    for(int i=0; i<model->getHealthpacks().size(); i++){
        if((model->getHealthpacks()[i]->getXPos()==posX)&&((model->getHealthpacks()[i]->getYPos()==posY))){
            return i;
        }
    }
    return -1;
}

void Controller::drinkPotion(int i){
    int EnergyProtagonist= model->getPikachu()->getEnergy();
    int HealthProtagonist= model->getPikachu()->getHealth();
    float heal = model->getHealthpacks()[i]->getValue();
    if(HealthProtagonist+heal>100){
        model->getPikachu()->setHealth(100);
    }
    if(EnergyProtagonist+heal>100){
        model->getPikachu()->setEnergy(100);
    }

    if(HealthProtagonist+heal<100){
        model->getPikachu()->setHealth(HealthProtagonist+heal);
    }

    if(EnergyProtagonist+heal<100){
        model->getPikachu()->setEnergy(EnergyProtagonist+heal);
    }
    std::cout<<"new life: "<<model->getPikachu()->getHealth()<<" new energy: "<< model->getPikachu()->getEnergy()<<std::endl;
    model->getHealthpacks()[i]->setValue(0);
    modelView->updatePotions(model);
}

void Controller::printPositionEnemies(){
    for(int i=0; i<model->getEnemies().size(); i++){
         std::cout<<model->getEnemies()[i]->getXPos()<<" and "<<model->getEnemies()[i]->getYPos()<<std::endl;
    }
}

bool Controller::move(std::string direction){
    int posX= model->getPikachu()->getXPos();
    int posY= model->getPikachu()->getYPos();
    int position = 0;
    if(direction=="Right"){
        posX++;
        position=2;
    }
    else if(direction=="Left"){
        posX--;
        position = 0;
    }
    else if(direction=="Up"){
        posY--;
        position = 1;
    }
    else if(direction=="Down"){
        posY++;
        position = 3;
    }
    int energy = model->getPikachu()->getEnergy();
    float tileValue = check(posX, posY);
    if ((tileValue<1)&&(tileValue>=0)){ // The value of posX needs to be checked before doing the tile value function
        if(energy-1-(tileValue)>0)
        {
            int potioncheck= checkPotion(posX,posY);
            if(potioncheck != -1){
                drinkPotion(checkPotion(posX,posY));
            }
            int poisonous = checkPoisonous(posX, posY);
            if(poisonous != -1){
                std::cout<<"this is a poisonous tile"<<std::endl;
                model->getPikachu()->setHealth((model->getPikachu()->getHealth())-((model->getPoisonousTiles()[poisonous])->getValue())/4);
                std::cout<<"value of the tile= "<<model->getPoisonousTiles()[poisonous]->getValue()<<std::endl;
            }
            int enemycheck= checkEnemy(posX,posY);
            if(enemycheck != -1){
                attackEnemy(enemycheck);
            }
            if(model->getPikachu()->getHealth()<1){
                lose();
            }
            if(tileValue<0.5){
                energy=model->getPikachu()->getEnergy()-1-(tileValue*2);
            }
            else{
                energy=model->getPikachu()->getEnergy()-1-(tileValue*10);
            }
            model->getPikachu()->setXPos(posX);
            model->getPikachu()->setYPos(posY);
            model->getPikachu()->setEnergy(energy);
            textScene->moveSegment();
            printProtagonistEnergy();
            return true;
        }
        std::cout<<"no energy"<<std::endl;
        return false;
    }
    else{
        std::cout<<"moving is not possible"<<std::endl;
        return false;
    }
}


void Controller::printProtagonistPosition(){
    std::cout<<model->getPikachu()->getXPos()<< std::endl;
    std::cout<<model->getPikachu()->getYPos()<< std::endl;
}

void Controller::printEnemyType(){
    for(int i=0; i<model->getEnemies().size(); i++){
        std::cout<<"the type is: "<<model->typeEnemy(i)<<std::endl;
    }
}

void Controller::printProtagonistHealth()
{
    std::cout<<this->model->getPikachu()->getHealth()<< std::endl;
}

void Controller::printProtagonistEnergy()
{
    std::cout<<this->model->getPikachu()->getEnergy()<< std::endl;
}


void Controller::printDimensions()
{
    std::cout<<model->getRows()<< std::endl;
    std::cout<<model->getCol()<< std::endl;
}

void Controller::printMap(){
    std::cout<<model->getGrid().size()<<std::endl;
    std::cout<<model->getCol()<<std::endl;
    for(int i=0; model->getGrid().size()-1; i++){
        if(model->getGrid()[i]->getValue()>0.9){
            std::cout<<"#";
            if((model->getGrid()[i]->getXPos())==(model->getCol()-1)){
               std::cout<<""<<std::endl;
            }
        }
        else{
        std::cout<<"[]";
            if((model->getGrid()[i]->getXPos())==(model->getCol()-1)){
                std::cout<<""<<std::endl;
            }
        }
    }
}


void Controller::win()
{
    std::cout << "You won!" << std::endl;
    //Needs an implementation in QGraphics
}



Model *Controller::getModel() const
{
    return model;
}

ModelView *Controller::getModelView() const
{
    return modelView;
}

void Controller::MoveXenemy(){
    for(int i=0; i<model->getEnemies().size(); i++){
            auto xenemy = std::dynamic_pointer_cast<Xenemy>(model->getEnemies()[i]);
            if((xenemy != nullptr)&&(xenemy->getDefeated()==false)){
                int x = xenemy->getXPos();
                int y = xenemy->getYPos();
                int random_dir = rand()%4;
                if(random_dir==1){ //right
                    x++;
                }
                if(random_dir==2){ //left
                    x--;
                }
                if(random_dir==3){ //down
                    y++;
                }
                if(random_dir==0){ //up
                    y--;
                }
                if(check(x, y)!=-1){
                    xenemy->setXPos(x);
                    xenemy->setYPos(y);
                    textScene->moveX(x,y,random_dir);
                    //xenemy-> emit XEnemyPositionchanged(x,y);
                }

            }
        }
    modelView->updateXenemies(model);
}

void Controller::printType(){
    for(int i=0; i<model->getEnemies().size(); i++){
        std::cout<<model->typeEnemy(i)<<std::endl;
    }
}






