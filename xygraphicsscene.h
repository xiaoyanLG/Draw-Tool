#ifndef XYGRAPHICSSCENE_H
#define XYGRAPHICSSCENE_H

#include <QGraphicsScene>

class XYGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum SHAPE{RECT, PATH, ELLIPSE};
    explicit XYGraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = Q_NULLPTR);
    ~XYGraphicsScene();
    SHAPE getShape();
    void setShape(SHAPE shape);

    void savePixmap(const QString &path);

protected:
    bool event(QEvent *event);

private:
    QGraphicsItem *getCurDrawshapeItem();
    void setGraphicsItemStartPos(QGraphicsItem *item, const QPointF &pos);
    void setGraphicsItemMovePos(QGraphicsItem *item, const QPointF &pos);

private:
    SHAPE meShape;
};

#endif // XYGRAPHICSSCENE_H
