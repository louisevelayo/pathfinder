#include "mainwindow.h"
#include <QApplication>
#include <memory>
#include <stdexcept>
#include <iostream>
#include "controller.h"
#include "qgraphicsview.h"
#include "protagonistview.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller controller{":/world_images/worldmap.png", 40, 40, 0.5, 0.2};
    ModelView *modelview = controller.getModelView();
    Model *model= controller.getModel();
    TextScene * textItem = controller.getTextScene();
    //textItem->setController(&controller);
    ModelView * twoScene = modelview;
    MainWindow w(twoScene,textItem,model,&controller);

   // w.connect(&w, SIGNAL(fileEntered(QString, int, int)), &controller, SLOT(openFile(QString,int,int)));

    w.show();
    return a.exec();
}
