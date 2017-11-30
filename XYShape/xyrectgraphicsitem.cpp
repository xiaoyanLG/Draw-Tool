#include "xyrectgraphicsitem.h"

XYRectGraphicsItem::XYRectGraphicsItem(const QRectF &rect, QGraphicsItem *parent)
    : XYGraphicsMovableItem(parent), moRect(rect)
{

}

QRectF XYRectGraphicsItem::boundingRect() const
{
    return moRect;
}

void XYRectGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *w)
{
    XYGraphicsMovableItem::paint(painter, option, w);
    painter->drawRect(moRect);
}
