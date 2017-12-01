#include "xyarrowsgraphicsitem.h"

XYArrowsGraphicsItem::XYArrowsGraphicsItem(const QPointF &start,
                                           const QPointF &end,
                                           QGraphicsItem *parent)
    : XYMovableGraphicsItem(parent)
{
    len = 16;
    startPos = start;
    endPos = end;
}

QRectF XYArrowsGraphicsItem::boundingRect() const
{
    QPainterPath path = getArrowsPath(startPos, endPos, len);
    return path.controlPointRect();
}

void XYArrowsGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *w)
{
    XYMovableGraphicsItem::paint(painter, option, w);
    QPainterPath path = getArrowsPath(startPos, endPos, len);
    painter->drawPath(path);
}

QPainterPath XYArrowsGraphicsItem::getArrowsPath(const QPointF &start,
                                                 const QPointF &end,
                                                 qreal len) const
{
    QPainterPath path;
    path.moveTo(start);

    QLineF line1 = getVerticalLine(end, start, len * sqrt(3) / 2, len / 2);
    QLineF line2 = getVerticalLine(end, start, len * sqrt(3) / 2, len);

    path.lineTo(line1.p1());
    path.lineTo(line2.p1());
    path.lineTo(end);
    path.lineTo(line2.p2());
    path.lineTo(line1.p2());
    path.lineTo(start);

    return path;
}
