#include "model_view.h"

Model_View::Model_View()
{
    pixelBased = true;

    }

bool Model_View::getPixelBased(){
    return pixelBased;
}

void Model_View::setPixelBased(bool pixel){
    pixelBased = pixel;
}

