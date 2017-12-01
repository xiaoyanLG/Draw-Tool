#ifndef XYGRAPHICSPATHITEM_H
#define XYGRAPHICSPATHITEM_H

#include "xymovablegraphicsitem.h"

class XYPathGraphicsItem : public XYMovableGraphicsItem
{
    Q_OBJECT
public:
    explicit XYPathGraphicsItem(const QPainterPath &path = QPainterPath(), QGraphicsItem *parent = 0);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *w) Q_DECL_OVERRIDE;
    bool isValid();

private:
    QPainterPath moPath;

    friend class XYGraphicsScene;
};

#endif // XYGRAPHICSPATHITEM_H
