#include "xymovablegraphicsitem.h"

bool XYMovableGraphicsItem::acceptMouse = false;
XYMovableGraphicsItem::XYMovableGraphicsItem(QGraphicsItem *parent)
    : XYShapeGraphicsItem(parent), selected(false)
{
    meType = XYSHAPEMOVABLE;
    setAcceptHoverEvents(true);
}

void XYMovableGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *w)
{
    XYShapeGraphicsItem::paint(painter, option, w);
    if (selected)
    {
        QPen pen = painter->pen();
        pen.setColor(QColor("red"));
        painter->setPen(pen);
    }
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
    selected = true;
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
    if (w * w + h * h < 10*10) // 控制误差范围
    {
        return false;
    }
    return true;
}

int XYMovableGraphicsItem::type() const
{
    return meType;
}

void XYMovableGraphicsItem::startCreateItem(const QPointF &pos)
{
    startPos = pos;
    endPos = pos;
}

void XYMovableGraphicsItem::duringCreateItem(const QPointF &pos)
{
    endPos = pos;
}

void XYMovableGraphicsItem::endCreateItem(const QPointF &pos)
{
    endPos = pos;
    selected = true;
    creating = false;
}
