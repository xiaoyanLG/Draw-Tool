#ifndef XYCANVASGRAPHICSITEM_H
#define XYCANVASGRAPHICSITEM_H

#include "xygraphicsshapeitem.h"

class XYCanvasGraphicsItem : public XYGraphicsShapeItem
{
    Q_OBJECT
public:
    explicit XYCanvasGraphicsItem(const QPixmap &pixmap = QPixmap(), QGraphicsItem *parent = 0);

    void setPixmap(const QPixmap &pixmap);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *) Q_DECL_OVERRIDE;

private:
    QPixmap backImage;
};

#endif // XYCANVASGRAPHICSITEM_H
