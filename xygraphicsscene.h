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
    enum SHAPE{RECT, POLYGON, PATH, ELLIPSE, LINE, ARROWS, TEXT, PIXMAP, CURSOR, DELETE};
    explicit XYGraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = Q_NULLPTR);
    ~XYGraphicsScene();
    SHAPE getShape();
    void setShape(SHAPE shape);
    void setItemMovable(bool movable);

    void setTextEdit(QTextEdit *textEdit);
    void addPixmapItem(const QString &file, const QPointF &pos);
    void savePixmap(const QString &path);
    void showTextEdit(XYTextGraphicsItem *item);

signals:
    void selectItemChanged(QGraphicsItem *selectItem);

public slots:
    void stickItem();
    void zoomUpItem();
    void zoomDownItem();
    void rotationItem();
    void setItemText();
    void slotPenChanged(const QPen &pen);
    void slotBrushChanged(const QBrush &brush);
    void slotFontChanged(const QFont &font);

protected:
    bool event(QEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

    bool paintPolygon(QEvent *event);

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
    QGraphicsItem *selectItem;
};

#endif // XYGRAPHICSSCENE_H
