#include "image.h"

Image::Image(QString path)
    : image(path)
{
    scaleFactor = 1;
    rotationAngle = 0.0;
}

Image::Image()
{
}

// ***********************************
//          G E T T E R S
// ***********************************
QImage* Image::getQImage()
{
    return &image;
}

QString Image::getPath()
{
    return path;
}

QRect Image::getCropArea()
{
    return cropArea;
}

double Image::getRotationAngle()
{
    return rotationAngle;
}

int Image::getScaleFactor()
{
    return scaleFactor;
}

// ***********************************
//          S E T T E R S
// ***********************************
void Image::setCropArea(QRect area)
{
    this->cropArea = area;
}

void Image::setQImage(QImage newImage)
{
    this->image = newImage;
}

void Image::setRotationAngle(double angle)
{
    this->rotationAngle = angle;
}

void Image::setScaleFactor(int sf)
{
    this->scaleFactor = sf;
}

// ***********************************
//           O p e r a t i o n s
// ***********************************
void Image::saveImage(QString path)
{
    // TODO save image using the information in this class.
}

void Image::reset()
{
    rotationAngle = 0;
    scaleFactor = 1;
    cropArea.setX(0);
    cropArea.setY(0);
    cropArea.setWidth(0);
    cropArea.setHeight(0);
}

