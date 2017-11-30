#include "xypathgraphicsitem.h"

XYPathGraphicsItem::XYPathGraphicsItem(const QPainterPath &path, QGraphicsItem *parent)
    : XYGraphicsMovableItem(parent), moPath(path)
{

}

QRectF XYPathGraphicsItem::boundingRect() const
{
    return moPath.controlPointRect();
}

void XYPathGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *w)
{
    XYGraphicsMovableItem::paint(painter, option, w);
    painter->drawPath(moPath);
}
