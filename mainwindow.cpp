#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "modelview.h"
#include <QWheelEvent>
#include <ostream>
#include <QApplication>
//#include <winsock.h>



MainWindow::MainWindow(ModelView * twoScene, TextScene* textScene,Model *model,Controller *controller, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->controller = controller;
    this->protagonist = controller->getModelView()->getProtagonist();
    ui->setupUi(this);
    ui->graphicsView->setScene(twoScene);
    ui->graphicsView->setController(controller);
    this->model = model;
    this->twoScene = twoScene;
    this->textScene = textScene;
    helpSent = 0;
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(move()));
    connect(ui->lineEdit, SIGNAL(textEdited(QString)), this, SLOT(textPrompt(QString)));
    ui->progressBar->setMaximum(model->getPikachu()->getHealth());
    ui->progressBar_2->setMaximum(model->getPikachu()->getEnergy());
    ui->progressBar->setValue(model->getPikachu()->getHealth());
    ui->progressBar_2->setValue(model->getPikachu()->getEnergy());
    ui->horizontalSlider->setMaximum(100);
    ui->horizontalSlider->setSliderPosition(0);
    connect(ui->autoplay, SIGNAL(pressed()), this, SLOT(clickonautoplay()));
    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(setWeightforpath(int)));
    connect(model->getPikachu(), SIGNAL(healthChanged(int)), ui->progressBar, SLOT(setValue(int)));
    connect(model->getPikachu(), SIGNAL(energyChanged(int)), ui->progressBar_2, SLOT(setValue(int)));
    connect(ui->mapButton, SIGNAL(clicked()), this, SLOT(mapButtonPushed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clickonautoplay(){
    std::cout<<"button clicked"<<std::endl;
    controller->autoclicked();
}

void MainWindow::setWeightforpath(int value){
    controller->setWeight(value);
}

void MainWindow::setText(){
    ui->graphicsView->setScene(textScene);
    ui->graphicsView->setFocus();
}

void MainWindow::set2D(){
    ui->graphicsView->setScene(twoScene);
    ui->graphicsView->setFocus();
}

void MainWindow::textPrompt(QString prompt){
    int action =0;
    if(prompt == "l"){
        protagonist->updateWithPrompt("left");
        action = 1;
    }
    else if(prompt == "u"){
        protagonist->updateWithPrompt("up");
        action = 1;
    }
    else if(prompt == "r"){
        protagonist->updateWithPrompt("right");
        action = 1;
    }
    else if(prompt == "d"){
        protagonist->updateWithPrompt("down");
        action = 1;
    }
    else if(prompt == "h"){
        if(helpSent == 0){
        QString messHelp;
        QTextStream stream(&messHelp);

        stream << "input the letter l to move left\n\n";
        stream << "input the letter u to move up\n\n";
        stream << "input the letter r to move right\n\n";
        stream << "input the letter d to move down\n\n";
        stream << "input the letter a to attack the nearest enemy\n\n";
        stream << "input the 'xCoordinate yCoordinate goto' to make Goomba go to those coordinates";

        messHelp = stream.readAll();
        ui->textEdit->setPlainText(messHelp);
        helpSent = 1;
        }
        action = 1;
    }
    else if(prompt == "a"){
        int enemyIndex = controller->getClosestEnemy();
        auto enemy= controller->getModel()->getEnemies()[enemyIndex];
        int x = enemy->getXPos();
        int y = enemy->getYPos();

        ui->graphicsView->usePathfind(x, y);
        ui->graphicsView->setActivatepathfinder(true);


        //function to attack nearest enemy
        action = 1;
    }
    else if(prompt.endsWith("goto",Qt::CaseInsensitive)) {
        QStringList list = prompt.split(" ");
        int xT = list[0].toInt();
        int yT = list[1].toInt();
        ui->graphicsView->usePathfind(xT, yT);
        ui->graphicsView->setActivatepathfinder(true);

//        std::cout << "x: " << xT << " y: " << yT << std::endl;
//        controller->findPath(controller->getModel()->getPikachu()->getXPos(),
//                             controller->getModel()->getPikachu()->getYPos(),
//                             xT,
//                             yT);
        action = 1;
    }
    if(action == 1){
        ui->lineEdit->clear();
    }
}

void MainWindow::mapButtonPushed()
{
    const QString file = QFileDialog::getOpenFileName(this,
                                                      "Select a new map",
                                                      "",
                                                      "Image Files (*.png *.jpg *.bmp)");

    if (file.isEmpty()) return;

    bool okEnemies;
    unsigned int enemies = QInputDialog::getInt(this,
                                       "Open new map",
                                       "Number of enemies:",
                                       10, 0, 300, 1,
                                       &okEnemies);

    if (!okEnemies) return;
    bool okHealthPacks;
    unsigned int healthPacks = QInputDialog::getInt(this,
                                           "Open new map",
                                           "Number of health packs:",
                                           10, 0, 300, 1,
                                           &okHealthPacks);

    if (!file.isEmpty() && okEnemies && okHealthPacks)
    {
        controller = new Controller(file, enemies, healthPacks, 0.5, 0.2);
        model= controller->getModel();
        textScene = controller->getTextScene();
        twoScene = controller->getModelView();
        protagonist = twoScene->getProtagonist();
        uiReset();
    }
}

void MainWindow::uiReset(){
    ui->graphicsView->setController(controller);
    ui->graphicsView->setScene(twoScene);
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(move()));
    connect(ui->lineEdit, SIGNAL(textEdited(QString)), this, SLOT(textPrompt(QString)));
    ui->progressBar->setMaximum(model->getPikachu()->getHealth());
    ui->progressBar_2->setMaximum(model->getPikachu()->getEnergy());
    ui->progressBar->setValue(model->getPikachu()->getHealth());
    ui->progressBar_2->setValue(model->getPikachu()->getEnergy());
    connect(model->getPikachu(), SIGNAL(healthChanged(int)), ui->progressBar, SLOT(setValue(int)));
    connect(model->getPikachu(), SIGNAL(energyChanged(int)), ui->progressBar_2, SLOT(setValue(int)));
    connect(ui->mapButton, SIGNAL(clicked()), this, SLOT(mapButtonPushed()));
}



