#include "poisonoustileview.h"

poisonTileView::poisonTileView(int size, int x, int y)
{
    tileSize = size;
    poison = new QGraphicsPixmapItem(QPixmap(":/world_images/NicePng_lava-png_2334439.png").scaled(tileSize,tileSize), this);
    poison->setZValue(6);
    poison->setPos(x,y);
    poison->setVisible(false);
}

void poisonTileView::show()
{
    poison->setVisible(true);
}
