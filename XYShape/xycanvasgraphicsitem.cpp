#include <QPainter>
#include <QGraphicsScene>

#include "xycanvasgraphicsitem.h"
#include "xyrectgraphicsitem.h"
#include "xypathgraphicsitem.h"
#include "xyellipsegraphicsitem.h"


XYCanvasGraphicsItem::XYCanvasGraphicsItem(const QPixmap &pixmap, QGraphicsItem *parent)
    : XYShapeGraphicsItem(parent), backImage(pixmap)
{

}

void XYCanvasGraphicsItem::setPixmap(const QPixmap &pixmap)
{
    backImage = pixmap;
}

QRectF XYCanvasGraphicsItem::boundingRect() const
{
    return backImage.rect();
}

void XYCanvasGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    int x = (scene()->sceneRect().width() - backImage.width()) / 2;
    int y = (scene()->sceneRect().height() - backImage.height()) / 2;
    painter->drawPixmap(x, y, backImage);
}

int XYCanvasGraphicsItem::type() const
{
    return XYCANVAS;
}
