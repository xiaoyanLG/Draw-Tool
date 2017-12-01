#include "xytextgraphicsitem.h"

XYTextGraphicsItem::XYTextGraphicsItem(const QString &text, QGraphicsItem *parent)
    : XYMovableGraphicsItem(parent)
{

}

QRectF XYTextGraphicsItem::boundingRect() const
{
    const qreal x1 = startPos.x();
    const qreal x2 = endPos.x();
    const qreal y1 = startPos.y();
    const qreal y2 = endPos.y();
    qreal lx = qMin(x1, x2);
    qreal rx = qMax(x1, x2);
    qreal ty = qMin(y1, y2);
    qreal by = qMax(y1, y2);
    return QRectF(lx, ty, rx - lx, by - ty);
}

void XYTextGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *w)
{
    XYMovableGraphicsItem::paint(painter, option, w);
    if (option->state & QStyle::State_MouseOver
            || option->state & QStyle::State_Selected
            || selected)
    {
        painter->drawRect(boundingRect());
    }
    painter->drawText(boundingRect(), msText);
}

void XYTextGraphicsItem::startCreateItem(const QPointF &pos)
{
    XYMovableGraphicsItem::startCreateItem(pos);
}

void XYTextGraphicsItem::endCreateItem(const QPointF &pos)
{
    XYMovableGraphicsItem::endCreateItem(pos);
}
