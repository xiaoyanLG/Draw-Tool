#include "xygraphicsmovableitem.h"

XYGraphicsMovableItem::XYGraphicsMovableItem(QGraphicsItem *parent)
    : XYGraphicsShapeItem(parent)
{
    setAcceptHoverEvents(true);
}

void XYGraphicsMovableItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (isHoverArea(event->scenePos()))
    {
        event->accept();
    }
}

void XYGraphicsMovableItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (isHoverArea(event->scenePos()))
    {
        event->accept();
    }
}

void XYGraphicsMovableItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    if (isHoverArea(event->scenePos()))
    {
        event->accept();
        setPos(pos() + event->scenePos() - event->lastScenePos());
    }
}

bool XYGraphicsMovableItem::isHoverArea(const QPointF &pos)
{
    return true;
}
