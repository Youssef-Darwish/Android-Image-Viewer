#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <QRect>
#include <QString>

class Image
{
public:
    Image(QString path);

    // getters
    QImage* getQImage();
    QString getPath();
    QRect getCropArea();
    double getRotationAngle();
    int getScaleFactor();
    QPixmap getPixMap();

    // setters
    void setCropArea(QRect);
    void setRotationAngle(double);
    void setScaleFactor(int);
    void setPixMap(QPixmap);
    void setQImage(QImage);

    // operation
    void saveImage(QString path);
    void reset();

private:
    Image();
    QString path;
    QImage image;
    double rotationAngle;
    QRect cropArea;
    int scaleFactor;
    QPixmap* pixmap;
};

#endif // IMAGE_H
