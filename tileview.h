#ifndef TILEVIEW_H
#define TILEVIEW_H
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <iostream>

class tileview : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    tileview();
    int getPosX() const;
    void setPosX(int newPosX);
    int getPosY() const;
    void setPosY(int newPosY);

private:
    float value;
    int endXCord;
    int endYCord;

signals:
    void findPath(int endXCord, int endYcord);

public slots:

private slots:
};

#endif // TILEVIEW_H
