#include "xypolygongraphicsitem.h"

XYPolygonGraphicsitem::XYPolygonGraphicsitem(QGraphicsItem *parent)
    : XYMovableGraphicsItem(parent)
{

}

XYPolygonGraphicsitem::~XYPolygonGraphicsitem()
{

}

QRectF XYPolygonGraphicsitem::boundingRect() const
{
    QPainterPath path;
    path.moveTo(startPos);
    for (int i = 0; i < allPoints.size(); ++i)
    {
        path.lineTo(allPoints.at(i));
    }
    path.lineTo(endPos);
    path.lineTo(startPos);
    return path.controlPointRect();
}

void XYPolygonGraphicsitem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *w)
{
    XYMovableGraphicsItem::paint(painter, option, w);
    QPainterPath path;
    path.moveTo(startPos);
    for (int i = 0; i < allPoints.size(); ++i)
    {
        path.lineTo(allPoints.at(i));
    }
    path.lineTo(endPos);
    path.lineTo(startPos);

    painter->drawPath(path);
}
