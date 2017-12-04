#include "xyrectgraphicsitem.h"

XYRectGraphicsItem::XYRectGraphicsItem(const QRectF &rect, QGraphicsItem *parent)
    : XYMovableGraphicsItem(parent), moRect(rect)
{

}

QRectF XYRectGraphicsItem::boundingRect() const
{
    return QRectF(moRect.x(), moRect.y(),
                  moRect.width() + 1, moRect.height() + 1);
}

void XYRectGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *w)
{
    XYMovableGraphicsItem::paint(painter, option, w);
    painter->drawRect(moRect);
}
