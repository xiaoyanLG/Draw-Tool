#ifndef XYGRAPHICSMOVABLEITEM_H
#define XYGRAPHICSMOVABLEITEM_H

#include "xyshapegraphicsitem.h"

class XYMovableGraphicsItem : public XYShapeGraphicsItem
{
    Q_OBJECT
public:
    enum XYTYPE { XYSHAPEMOVABLE = XYSHAPE + 1, XYTEXT };
    explicit XYMovableGraphicsItem(QGraphicsItem *parent = 0);

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *w) Q_DECL_OVERRIDE;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

    // 指示该区域是否是悬浮区域(子类可以重写)
    virtual bool isHoverArea(const QPointF &pos);
    virtual bool isValid();
    virtual int type() const;

    virtual void startCreateItem(const QPointF &pos);
    virtual void duringCreateItem(const QPointF &pos);
    virtual void endCreateItem(const QPointF &pos);

protected:
    QPointF startPos;
    QPointF endPos;
    XYTYPE  meType;
    bool    selected;
    static  bool acceptMouse;

    friend class XYGraphicsScene;
};

#endif // XYGRAPHICSMOVABLEITEM_H
