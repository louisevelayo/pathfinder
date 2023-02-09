#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class MouseEvent : public QObject, public QGraphicsPixmapItem
{
public:
    MouseEvent(QPixmap image);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *ev) override;

signals:
    mapClicked(QPoint point, float value);

};

#endif // MOUSEEVENT_H
