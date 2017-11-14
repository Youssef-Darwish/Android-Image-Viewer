#ifndef QGRAPHICSVIEWN_H
#define QGRAPHICSVIEWN_H

#include <QWidget>
#include <QGraphicsView>
#include <QPoint>
#include <QMouseEvent>
#include <QRect>
#include <QTouchEvent>
#include <QRubberBand>
#include <QDebug>
#include <cstdlib>
#include <QScrollBar>
#include <QTouchEvent>
#include <QDebug>


class QGraphicsViewn : public QGraphicsView
{
    Q_OBJECT
private:
    QPoint press,release;
    QRubberBand *rubber_band;
    qreal totalScaleFactor;

public:
    explicit QGraphicsViewn(QWidget *parent = nullptr);
    QRect* get_selected();
    bool viewportEvent(QEvent *event);

signals:
    void area_selected();

public slots:
    void select();
    void unselect();

protected slots:
    void pressPoint(QPointF pres);
    void releasePoint(QPointF pres);
    void movePoint(QPointF pres);
};

#endif // QGRAPHICSVIEWN_H
