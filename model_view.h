#ifndef MODEL_VIEW_H
#define MODEL_VIEW_H
#include "Model.h"
#include <QGraphicsPixmapItem>


class Model_View: public QGraphicsPixmapItem
{
public:
    Model_View();
    bool getPixelBased();
    void setPixelBased(bool pixel);


private:
    bool pixelBased;

};

#endif // MODEL_VIEW_H
