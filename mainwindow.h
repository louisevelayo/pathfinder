#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QInputDialog>
#include "qgraphicsscene.h"
#include "world.h"
#include "Model.h"
#include "textscene.h"
#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(ModelView *, TextScene *, Model *,Controller* ,QWidget *parent = nullptr);
    ~MainWindow();
    std::string serialize();
    void setMapText();


    Ui::MainWindow *getUi() const;
    void uiReset();

    int helpSent;



public slots:
    void setText();
    void set2D();

    void setWeightforpath(int value);

    void clickonautoplay();
private slots:
    void textPrompt(QString);
    void mapButtonPushed();

signals:
    void fileEntered(const QString fileName, int enemies, int healthPacks);



private:
    Ui::MainWindow *ui;
    Model *model;
    ModelView *twoScene;
    TextScene *textScene;
    Controller *controller;
    ProtagonistView * protagonist;
};
#endif // MAINWINDOW_H
