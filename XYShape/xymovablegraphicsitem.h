#ifndef XYGRAPHICSMOVABLEITEM_H
#define XYGRAPHICSMOVABLEITEM_H

#include "xyshapegraphicsitem.h"

class XYMovableGraphicsItem : public XYShapeGraphicsItem
{
    Q_OBJECT
public:
    explicit XYMovableGraphicsItem(QGraphicsItem *parent = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

    // 指示该区域是否是悬浮区域(子类可以重写)
    virtual bool isHoverArea(const QPointF &pos);
    bool isValid();

public slots:

protected:
    QPointF startPos;
    QPointF endPos;
    static  bool acceptMouse;

    friend class XYGraphicsScene;
};

#endif // XYGRAPHICSMOVABLEITEM_H
