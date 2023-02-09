#include "mouseevent.h"

MouseEvent::MouseEvent(QPixmap image) : QGraphicsPixmapItem{image}
{
    setZValue(0);
}

void MouseEvent::mousePressEvent(QGraphicsSceneMouseEvent *ev){
    if(ev->button() == Qt::LeftButton){
        if(ev->modifiers() & Qt::ShiftModifier){
            QPointF point = ev->scenePos();
            int x = floor(point.x() / 30);
            int y = floor(point.y() / 30);
            emit mapClicked(QPoint(x,y), -1.0f);
        }
    }
}
