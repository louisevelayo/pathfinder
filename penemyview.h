#ifndef PENEMYVIEW_H
#define PENEMYVIEW_H
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsItemGroup>


class PenemyView : public QObject, public QGraphicsPixmapItem
{
public:
    PenemyView(int size, int x, int y, int poisonlevel, int value);
private:
    QGraphicsPixmapItem *enemy, *deadenemy;
    std::vector<QGraphicsRectItem*> poison;
    QGraphicsRectItem *poisonous;
    QGraphicsTextItem *strenght;
    int maxpoison;
    int green;
    int tileSize;
public slots:
    void ondead();
    void onpoisonchange(int value);
};

#endif // PENEMYVIEW_H
