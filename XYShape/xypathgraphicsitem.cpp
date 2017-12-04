#include "xypathgraphicsitem.h"

XYPathGraphicsItem::XYPathGraphicsItem(const QPainterPath &path, QGraphicsItem *parent)
    : XYMovableGraphicsItem(parent), moPath(path)
{

}

QRectF XYPathGraphicsItem::boundingRect() const
{
    return moPath.controlPointRect();
}

void XYPathGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *w)
{
    XYMovableGraphicsItem::paint(painter, option, w);
    painter->drawPath(moPath);
}

bool XYPathGraphicsItem::isValid()
{
    int w = moPath.controlPointRect().size().width();
    int h = moPath.controlPointRect().size().height();
    if (w * w + h * h < 5*5)
    {
        return false;
    }
    return true;
}
