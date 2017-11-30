#ifndef XYGRAPHICSPATHITEM_H
#define XYGRAPHICSPATHITEM_H

#include "xygraphicsmovableitem.h"

class XYPathGraphicsItem : public XYGraphicsMovableItem
{
    Q_OBJECT
public:
    explicit XYPathGraphicsItem(const QPainterPath &path = QPainterPath(), QGraphicsItem *parent = 0);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *w) Q_DECL_OVERRIDE;

private:
    QPainterPath moPath;

    friend class XYGraphicsScene;
};

#endif // XYGRAPHICSPATHITEM_H
