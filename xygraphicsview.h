#ifndef XYGRAPHICSVIEW_H
#define XYGRAPHICSVIEW_H

#include <QGraphicsView>

class XYGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit XYGraphicsView(QGraphicsScene *scene = 0);
    ~XYGraphicsView();

protected:
    void wheelEvent(QWheelEvent *event);
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;

};

#endif // XYGRAPHICSVIEW_H
