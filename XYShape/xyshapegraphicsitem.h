#ifndef XYGRAPHICSSHAPEITEM_H
#define XYGRAPHICSSHAPEITEM_H

#include <QObject>
#include <QAbstractGraphicsShapeItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

class XYShapeGraphicsItem : public QObject, public QAbstractGraphicsShapeItem
{
    Q_OBJECT
public:
    enum { XYSHAPE = UserType + 1 };
    explicit XYShapeGraphicsItem(QGraphicsItem *parent = 0);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *) Q_DECL_OVERRIDE;
    virtual bool isValid();
    int type() const;

    QPen  getPaintPen() const;
    QFont getFont() const;
    void setFont(const QFont &value);

public:
    static QLineF getEllipseAndLineNodes(qreal k, qreal b, qreal c, qreal d, qreal r);
    static QLineF getVerticalLine(const QPointF &start,  // 获取一条直线的垂直线
                           const QPointF &end,
                           qreal distance,
                           qreal len);

    bool   creating;
    QFont  moFont;
    QPen   paintPen;

};

#endif // XYGRAPHICSSHAPEITEM_H
