#ifndef XYPIXMAPGRAPHICSITEM_H
#define XYPIXMAPGRAPHICSITEM_H

#include <QGraphicsPixmapItem>

class XYPixmapGraphicsItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit XYPixmapGraphicsItem(const QPixmap &pixmap = QPixmap(),
                                  QGraphicsItem *parent = 0);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private: // 这个类单独实现paint函数在移动的时候会出现问题，目前不知道怎么实现，转而继承QT自身实现的
    friend class XYGraphicsScene;
};

#endif // XYPIXMAPGRAPHICSITEM_H
