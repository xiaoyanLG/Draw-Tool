#include "xygraphicsshapeitem.h"

XYGraphicsShapeItem::XYGraphicsShapeItem(QGraphicsItem *parent)
    : QAbstractGraphicsShapeItem(parent)
{

}

QRectF XYGraphicsShapeItem::boundingRect() const
{
    return QRectF(0, 0, 10, 10);
}

void XYGraphicsShapeItem::paint(QPainter *painter,
                                const QStyleOptionGraphicsItem *option,
                                QWidget *)
{
    if (option->state & QStyle::State_MouseOver)
    {
        painter->setPen(QColor("red"));
    }
}
