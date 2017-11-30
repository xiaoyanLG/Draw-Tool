#include "xyellipsegraphicsitem.h"

XYEllipseGraphicsItem::XYEllipseGraphicsItem(const QRectF &rect, QGraphicsItem *parent)
    : XYGraphicsMovableItem(parent), moRect(rect)
{

}

QRectF XYEllipseGraphicsItem::boundingRect() const
{
    return moRect;
}

void XYEllipseGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *w)
{
    XYGraphicsMovableItem::paint(painter, option, w);
    painter->drawEllipse(moRect);
}
