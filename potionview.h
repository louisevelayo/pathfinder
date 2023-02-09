#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsItemGroup>

class potiontileView : public QObject, public QGraphicsPixmapItem
{
public:
    potiontileView(int size, int x, int y);

    int getDrinked() const;

private:
    int tileSize;
    QGraphicsPixmapItem* potion, *deadpotion;
    int drinked;

public slots:
    void updatedrinked();
};
