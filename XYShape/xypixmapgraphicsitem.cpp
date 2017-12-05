#include "xypixmapgraphicsitem.h"
#include "xygraphicsscene.h"
#include <QGraphicsSceneMouseEvent>

XYPixmapGraphicsItem::XYPixmapGraphicsItem(const QPixmap &pixmap, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap, parent), QObject()
{
    setCacheMode(DeviceCoordinateCache);
}

void XYPixmapGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void XYPixmapGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void XYPixmapGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    setPos(pos() + event->scenePos() - event->lastScenePos());
}
