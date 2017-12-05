#ifndef XYCANVASGRAPHICSITEM_H
#define XYCANVASGRAPHICSITEM_H

#include "xyshapegraphicsitem.h"

class XYCanvasGraphicsItem : public XYShapeGraphicsItem
{
    Q_OBJECT
public:
    enum {XYCANVAS = XYSHAPE + 10};
    explicit XYCanvasGraphicsItem(const QPixmap &pixmap = QPixmap(), QGraphicsItem *parent = 0);

    void setPixmap(const QPixmap &pixmap);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *) Q_DECL_OVERRIDE;

    int type() const;

private:
    QPixmap backImage;
};

#endif // XYCANVASGRAPHICSITEM_H
