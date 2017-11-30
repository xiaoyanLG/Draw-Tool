#ifndef XYGRAPHICSVIEW_H
#define XYGRAPHICSVIEW_H

#include <QGraphicsView>

class XYGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit XYGraphicsView(QGraphicsScene *scene = 0);
    ~XYGraphicsView();

};

#endif // XYGRAPHICSVIEW_H
