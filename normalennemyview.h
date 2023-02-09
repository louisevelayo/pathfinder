#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsItemGroup>

class normalEnnemyView : public QObject, public QGraphicsPixmapItem
{
public:
    normalEnnemyView(int size, int x, int y, int value);

private:
    int tileSize;
    QGraphicsPixmapItem* ennemy, *deadennemy;
    QGraphicsTextItem *strenght;

public slots:
    void ondead();
};
