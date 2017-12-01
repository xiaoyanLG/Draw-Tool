#ifndef XYARROWSGRAPHICSITEM_H
#define XYARROWSGRAPHICSITEM_H

#include "xymovablegraphicsitem.h"

class XYArrowsGraphicsItem : public XYMovableGraphicsItem
{
    Q_OBJECT
public:
    explicit XYArrowsGraphicsItem(const QPointF &start = QPointF(),
                                  const QPointF &end = QPointF(),
                                  QGraphicsItem *parent = 0);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *w) Q_DECL_OVERRIDE;

private:
    QPainterPath getArrowsPath(const QPointF &start,
                               const QPointF &end,
                               qreal len) const;

private:
    qreal   len;

    friend class XYGraphicsScene;
};

#endif // XYARROWSGRAPHICSITEM_H
