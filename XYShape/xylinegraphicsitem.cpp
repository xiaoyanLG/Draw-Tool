#include "xylinegraphicsitem.h"

XYLineGraphicsItem::XYLineGraphicsItem(const QLineF &line, QGraphicsItem *parent)
    : XYMovableGraphicsItem(parent)
{

}

QRectF XYLineGraphicsItem::boundingRect() const
{
    const qreal x1 = moLine.p1().x();
    const qreal x2 = moLine.p2().x();
    const qreal y1 = moLine.p1().y();
    const qreal y2 = moLine.p2().y();
    qreal lx = qMin(x1, x2);
    qreal rx = qMax(x1, x2);
    qreal ty = qMin(y1, y2);
    qreal by = qMax(y1, y2);
    return QRectF(lx, ty, rx - lx, by - ty);
}

void XYLineGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *w)
{
    XYMovableGraphicsItem::paint(painter, option, w);
    painter->drawLine(moLine);
}
