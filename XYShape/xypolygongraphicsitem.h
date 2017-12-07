#ifndef XYPOLYGONGRAPHICSITEM_H
#define XYPOLYGONGRAPHICSITEM_H

#include "xymovablegraphicsitem.h"

class XYPolygonGraphicsitem : public XYMovableGraphicsItem
{
    Q_OBJECT
public:
    explicit XYPolygonGraphicsitem(QGraphicsItem *parent = 0);
    ~XYPolygonGraphicsitem();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *w) Q_DECL_OVERRIDE;

private:
    QList<QPointF> allPoints;

    friend class XYGraphicsScene;
};

#endif // XYPOLYGONGRAPHICSITEM_H
