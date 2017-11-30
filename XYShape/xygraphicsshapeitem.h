#ifndef XYGRAPHICSSHAPEITEM_H
#define XYGRAPHICSSHAPEITEM_H

#include <QObject>
#include <QAbstractGraphicsShapeItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

class XYGraphicsShapeItem : public QObject, public QAbstractGraphicsShapeItem
{
    Q_OBJECT
public:
    explicit XYGraphicsShapeItem(QGraphicsItem *parent = 0);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *) Q_DECL_OVERRIDE;
};

#endif // XYGRAPHICSSHAPEITEM_H
