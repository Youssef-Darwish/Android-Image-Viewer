#include "qgraphicsviewn.h"


using namespace std;

int totalFinalScale=0;


QGraphicsViewn::QGraphicsViewn(QWidget *parent) : QGraphicsView(parent)
{
    rubber_band = NULL;
    viewport()->setAttribute(Qt::WA_AcceptTouchEvents);
    setDragMode(ScrollHandDrag);

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
qreal accfactor = 1;
int dummy_count = 0;
bool QGraphicsViewn::viewportEvent(QEvent *event)
{
    switch (event->type()) {
    case QEvent::TouchBegin:
        accfactor = 1;
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
    {
        QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
        QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();
        if (touchPoints.count() == 2) {
            // determine scale factor
            const QTouchEvent::TouchPoint &touchPoint0 = touchPoints.first();
            const QTouchEvent::TouchPoint &touchPoint1 = touchPoints.last();
            qreal currentScaleFactor =
                    QLineF(touchPoint0.pos(), touchPoint1.pos()).length()
                    / QLineF(touchPoint0.startPos(), touchPoint1.startPos()).length();
            accfactor = currentScaleFactor / accfactor;
            //            if (touchEvent->touchPointStates() & Qt::TouchPointReleased) {
                // if one of the fingers is released, remember the current scale
                // factor so that adding another finger later will continue zooming
                // by adding new scale factor to the existing remembered value.
//                totalScaleFactor *= currentScaleFactor;
//                currentScaleFactor = 1;
//            }




           dummy_count++;
           if (dummy_count < 4) return true;
            totalScaleFactor=1;

            if (currentScaleFactor > 1) {
                if(totalFinalScale>40)
                    return true;
                 totalFinalScale++;
            } else {
                if(totalFinalScale<-40)
                    return true;
                 totalFinalScale--;
            }


           // qDebug() << "the scale::" << currentScaleFactor << "\ntotal scal: " << totalScaleFactor << "\n";
            //setTransform(QTransform().scale(totalScaleFactor * currentScaleFactor,
                 //                           totalScaleFactor * currentScaleFactor),true);
            qDebug() << "the scale::" << totalFinalScale <<"\n" ;

            setTransform(QTransform().scale(totalScaleFactor * accfactor,
                                            totalScaleFactor * accfactor),true);
           // dummy_count = 0;
        }
        return true;
    }
    default:
        break;
    }
    return QGraphicsView::viewportEvent(event);
}

