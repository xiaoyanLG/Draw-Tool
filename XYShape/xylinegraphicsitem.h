#ifndef XYLINEGRAPHICSITEM_H
#define XYLINEGRAPHICSITEM_H

#include "xymovablegraphicsitem.h"

class XYLineGraphicsItem : public XYMovableGraphicsItem
{
    Q_OBJECT
public:
    explicit XYLineGraphicsItem(const QLineF &line = QLineF(), QGraphicsItem *parent = 0);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *w) Q_DECL_OVERRIDE;
private:
    QLineF  moLine;

    friend class XYGraphicsScene;
};

#endif // XYLINEGRAPHICSITEM_H
