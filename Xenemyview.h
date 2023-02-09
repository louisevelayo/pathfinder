#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsItemGroup>

class XEnemyView : public QObject, public QGraphicsPixmapItem
{
public:
    XEnemyView(int size, int x, int y, int value);

private:
    int tileSize;
    QGraphicsPixmapItem* ennemy, *deadennemy;
    QGraphicsTextItem *strenght;

public slots:
    void ondead();
    void updatepos(int x, int y);
};
