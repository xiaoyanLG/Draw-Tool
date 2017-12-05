#include "xygraphicsview.h"
#include <QWheelEvent>

XYGraphicsView::XYGraphicsView(QGraphicsScene *scene)
    : QGraphicsView(scene)
{

}

XYGraphicsView::~XYGraphicsView()
{

}

void XYGraphicsView::wheelEvent(QWheelEvent *event)
{
    QGraphicsView::wheelEvent(event);
    if (event->isAccepted())
    {
        return;
    }
    qreal unit = 0.02;
    QMatrix mat = matrix();
    if (event->delta() > 0)
    {
        mat.scale(1 + unit, 1 + unit);
    }
    else
    {
        mat.scale(1 - unit, 1 - unit);
    }
    setMatrix(mat);
}

void XYGraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
    // QTBUG 没有重写这个函数接收不到事件
}
