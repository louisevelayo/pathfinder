#include "tileview.h"

tileview::tileview()
{

}

int tileview::getPosX() const
{
    return endXCord;
}

void tileview::setPosX(int newPosX)
{
    endXCord = newPosX;
}

int tileview::getPosY() const
{
    return endYCord;
}

void tileview::setPosY(int newPosY)
{
    endYCord = newPosY;
}


//void tileview::mousePressEvent(QMouseEvent *event)
//{
//    if(event->modifiers() & Qt::ShiftModifier){
//        auto posClicked = mapToScene(event->pos());
//        auto x{posClicked.x()},y{posClicked.y()};

//        if(x<0||y<0) return;
//        //TODO: input max screen width and height.
//        if(x>)
//    }
//    std::cout << "clicked this tile " << std::endl;
//    emit findPath(endXCord, endYCord);
//}
