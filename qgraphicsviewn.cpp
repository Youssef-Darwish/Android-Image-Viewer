#include "qgraphicsviewn.h"

using namespace std;

QGraphicsViewn::QGraphicsViewn(QWidget *parent) : QGraphicsView(parent)
{
    rubber_band = NULL;
}

void QGraphicsViewn::mousePressEvent(QMouseEvent * event)
{
    QGraphicsView::mousePressEvent(event);
    press = event->pos();

    press.setX(min(press.x(),this->size().width()));
    press.setY(min(press.y(),this->size().height()));
    press.setX(max(press.x(),0));
    press.setY(max(press.y(),0));
}

QRect QGraphicsViewn::get_selected()
{
    QPoint start,end;
    start.setX(min(press.x(),release.x()));
    start.setY(min(press.y(),release.y()));
    end.setX(max(press.x(),release.x()));
    end.setY(max(press.y(),release.y()));

    QRect ret;
    ret.setX(start.x());
    ret.setY(start.y());
    ret.setWidth(end.x()-start.x());
    ret.setHeight(end.y()-start.y());
    return ret;
}

void QGraphicsViewn::mouseReleaseEvent(QMouseEvent * event)
{
    QGraphicsView::mouseReleaseEvent(event);
    release = event->pos();

    release.setX(min(release.x(),this->size().width()));
    release.setY(min(release.y(),this->size().height()));
    release.setX(max(release.x(),0));
    release.setY(max(release.y(),0));
    area_selected();
}


void QGraphicsViewn::mouseMoveEvent(QMouseEvent * event) {
    QGraphicsView::mouseMoveEvent(event);
    release = event->pos();

    release.setX(min(release.x(),this->size().width()));
    release.setY(min(release.y(),this->size().height()));
    release.setX(max(release.x(),0));
    release.setY(max(release.y(),0));
    area_selected();
}

void QGraphicsViewn::select() {
    if (!rubber_band)
           rubber_band = new QRubberBand(QRubberBand::Rectangle, this);
       rubber_band->setGeometry(get_selected());
       rubber_band->show();
}
void QGraphicsViewn::unselect() {
    if(!rubber_band)
        return;
    rubber_band->hide();
          delete rubber_band;
    rubber_band = NULL;
}
