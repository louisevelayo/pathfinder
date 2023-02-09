#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsItemGroup>

class poisonTileView : public QObject, public QGraphicsPixmapItem
{
public:
    poisonTileView(int size, int x, int y);

private:
    int tileSize;
    QGraphicsPixmapItem* poison;

public slots:
    void show();
};

