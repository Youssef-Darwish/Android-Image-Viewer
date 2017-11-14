#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <QRect>
#include <QString>

class Image
{
public:
    Image(QString path);
    Image();
    // getters
    QImage* getOrignal();
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
    void setOrignal(QImage);

    // operation
    void saveImage(QString path);
    void reset();

private:

    QString path;
    QImage image;
    double rotationAngle;
    QRect cropArea;
    int scaleFactor;
    QPixmap* pixmap;
    QImage original;
};

#endif // IMAGE_H
