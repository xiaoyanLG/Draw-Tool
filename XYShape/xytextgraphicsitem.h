#ifndef XYTEXTGRAPHICSITEM_H
#define XYTEXTGRAPHICSITEM_H

#include "xymovablegraphicsitem.h"

class XYTextGraphicsItem : public XYMovableGraphicsItem
{
    Q_OBJECT
public:
    explicit XYTextGraphicsItem(const QString &text = QString(), QGraphicsItem *parent = 0);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *w) Q_DECL_OVERRIDE;

    virtual void startCreateItem(const QPointF &pos);
    virtual void endCreateItem(const QPointF &pos);

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;

private:
    QFont moFont;
    QString msText;

    friend class XYGraphicsScene;
};

#endif // XYTEXTGRAPHICSITEM_H
