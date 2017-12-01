#include "xymovablegraphicsitem.h"

bool XYMovableGraphicsItem::acceptMouse = false;
XYMovableGraphicsItem::XYMovableGraphicsItem(QGraphicsItem *parent)
    : XYShapeGraphicsItem(parent)
{
    setAcceptHoverEvents(true);
}

void XYMovableGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!acceptMouse)
    {
        return QGraphicsItem::mousePressEvent(event);
    }
    if (isHoverArea(event->scenePos()))
    {
        event->accept();
    }
}

void XYMovableGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (!acceptMouse)
    {
        return QGraphicsItem::mouseReleaseEvent(event);
    }
    if (isHoverArea(event->scenePos()))
    {
        event->accept();
    }
}

void XYMovableGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (!acceptMouse)
    {
        return QGraphicsItem::mouseMoveEvent(event);
    }
    if (isHoverArea(event->scenePos()))
    {
        event->accept();
        setPos(pos() + event->scenePos() - event->lastScenePos());
    }
}

bool XYMovableGraphicsItem::isHoverArea(const QPointF &pos)
{
    return true;
}

bool XYMovableGraphicsItem::isValid()
{
    int w = startPos.x() - endPos.x();
    int h = startPos.y() - endPos.y();
    if (w * w + h * h < 5*5) // 控制误差范围
    {
        return false;
    }
    return true;
}

void XYMovableGraphicsItem::startCreateItem(const QPointF &pos)
{
    selected = true;
    startPos = pos;
    endPos = pos;
}

void XYMovableGraphicsItem::duringCreateItem(const QPointF &pos)
{
    selected = true;
    endPos = pos;
}

void XYMovableGraphicsItem::endCreateItem(const QPointF &pos)
{
    selected = false;
    endPos = pos;
}
