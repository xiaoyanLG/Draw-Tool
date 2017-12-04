#ifndef XYGRAPHICSSCENE_H
#define XYGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QTextEdit>

class XYMovableGraphicsItem;
class XYTextGraphicsItem;
class XYGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum SHAPE{RECT, PATH, ELLIPSE, LINE, ARROWS, TEXT, CURSOR, DELETE};
    explicit XYGraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = Q_NULLPTR);
    ~XYGraphicsScene();
    SHAPE getShape();
    void setShape(SHAPE shape);
    void setItemMovable(bool movable);

    void setTextEdit(QTextEdit *textEdit);
    void savePixmap(const QString &path);
    void showTextEdit(XYTextGraphicsItem *item);

public slots:
    void setItemText();

protected:
    bool event(QEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    QPen getCurPen();
    QFont getCurFont();
    QBrush getCurBrush();
    XYMovableGraphicsItem *getCurDrawshapeItem();
    void setGraphicsItemStartPos(XYMovableGraphicsItem *item, const QPointF &pos);
    void setGraphicsItemEndPos(XYMovableGraphicsItem *item, const QPointF &pos);
    void setGraphicsItemMovePos(XYMovableGraphicsItem *item, const QPointF &pos);

private:
    SHAPE meShape;
    QTextEdit *textEdit;
    XYTextGraphicsItem *haveKeyboardItem;
};

#endif // XYGRAPHICSSCENE_H
