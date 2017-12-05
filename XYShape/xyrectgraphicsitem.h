#ifndef XYGRAPHICSRECTITEM_H
#define XYGRAPHICSRECTITEM_H

#include "xymovablegraphicsitem.h"

class XYRectGraphicsItem : public XYMovableGraphicsItem
{
    Q_OBJECT
public:
    explicit XYRectGraphicsItem(const QRectF &rect = QRectF(), QGraphicsItem *parent = 0);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *w) Q_DECL_OVERRIDE;

private:
    QRectF moRect;

    friend class XYGraphicsScene;
};

#endif // XYGRAPHICSRECTITEM_H
