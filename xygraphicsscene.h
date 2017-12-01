#ifndef XYGRAPHICSSCENE_H
#define XYGRAPHICSSCENE_H

#include <QGraphicsScene>

class XYShapeGraphicsItem;
class XYGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum SHAPE{RECT, PATH, ELLIPSE, LINE, ARROWS, TEXT, CURSOR};
    explicit XYGraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = Q_NULLPTR);
    ~XYGraphicsScene();
    SHAPE getShape();
    void setShape(SHAPE shape);
    void setItemMovable(bool movable);

    void savePixmap(const QString &path);

protected:
    bool event(QEvent *event);

private:
    XYShapeGraphicsItem *getCurDrawshapeItem();
    void setGraphicsItemStartPos(XYShapeGraphicsItem *item, const QPointF &pos);
    void setGraphicsItemEndPos(XYShapeGraphicsItem *item, const QPointF &pos);
    void setGraphicsItemMovePos(XYShapeGraphicsItem *item, const QPointF &pos);

private:
    SHAPE meShape;

};

#endif // XYGRAPHICSSCENE_H
