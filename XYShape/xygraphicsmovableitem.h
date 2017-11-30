#ifndef XYGRAPHICSMOVABLEITEM_H
#define XYGRAPHICSMOVABLEITEM_H

#include "xygraphicsshapeitem.h"

class XYGraphicsMovableItem : public XYGraphicsShapeItem
{
    Q_OBJECT
public:
    explicit XYGraphicsMovableItem(QGraphicsItem *parent = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

    // 指示该区域是否是悬浮区域(子类可以重写)
    virtual bool isHoverArea(const QPointF &pos);

public slots:
};

#endif // XYGRAPHICSMOVABLEITEM_H
