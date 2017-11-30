#include "xygraphicsscene.h"
#include "xyrectgraphicsitem.h"
#include "xypathgraphicsitem.h"
#include "xyellipsegraphicsitem.h"

XYGraphicsScene::XYGraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent)
    : QGraphicsScene(x, y, width, height, parent)
{
    meShape = ELLIPSE;
}

XYGraphicsScene::~XYGraphicsScene()
{

}

XYGraphicsScene::SHAPE XYGraphicsScene::getShape()
{
    return meShape;
}

void XYGraphicsScene::setShape(XYGraphicsScene::SHAPE shape)
{
    meShape = shape;
}

void XYGraphicsScene::savePixmap(const QString &path)
{
    QPixmap pixmap;
    QPainter painter(&pixmap);
    this->render(&painter);
    pixmap.save(path);
}

bool XYGraphicsScene::event(QEvent *event)
{
    static QGraphicsItem *item = NULL;
    QGraphicsScene::event(event);
    if (event->isAccepted())
    {
        return true;
    }

    QGraphicsSceneMouseEvent *mouse_event = (QGraphicsSceneMouseEvent *)event;
    if (event->type() == QEvent::GraphicsSceneMousePress)
    {
        if (mouse_event->button() == Qt::LeftButton)
        {
            item = getCurDrawshapeItem();
            setGraphicsItemStartPos(item, mouse_event->scenePos());
            if (item)
            {
                this->addItem(item);
            }
        }
        else if (mouse_event->button() == Qt::RightButton)
        {
            if (item)
            {
                this->removeItem(item);
                delete item;
                item = NULL;
            }
        }
    }
    else if (event->type() == QEvent::GraphicsSceneMouseRelease)
    {
        if (mouse_event->button() == Qt::LeftButton)
        {
            if (item)
            {
                setGraphicsItemMovePos(item, mouse_event->scenePos());
                this->removeItem(item);
                this->addItem(item);
                item = NULL;
            }
        }
    }
    else if (event->type() == QEvent::GraphicsSceneMouseMove)
    {
        if (item)
        {
            setGraphicsItemMovePos(item, mouse_event->scenePos());
            update(this->sceneRect());
        }
    }
    event->accept();
    return true;
}

QGraphicsItem *XYGraphicsScene::getCurDrawshapeItem()
{
    QGraphicsItem *item = NULL;
    switch (meShape)
    {
    case RECT:
        item = new XYRectGraphicsItem;
        break;
    case PATH:
        item = new XYPathGraphicsItem;
        break;
    case ELLIPSE:
        item = new XYEllipseGraphicsItem;
        break;
    default:
        break;
    }

    return item;
}

void XYGraphicsScene::setGraphicsItemStartPos(QGraphicsItem *item, const QPointF &pos)
{
    switch (meShape)
    {
    case RECT:
    {
        XYRectGraphicsItem *rectItem = static_cast<XYRectGraphicsItem *>(item);
        if (rectItem)
        {
            rectItem->startPos = pos;
        }
        break;
    }
    case PATH:
    {
        XYPathGraphicsItem *pathItem = static_cast<XYPathGraphicsItem *>(item);
        if (pathItem)
        {
            pathItem->moPath.moveTo(pos);
        }
        break;
    }
    case ELLIPSE:
    {
        XYEllipseGraphicsItem *rectItem = static_cast<XYEllipseGraphicsItem *>(item);
        if (rectItem)
        {
            rectItem->startPos = pos;
        }
        break;
    }
    default:
        break;
    }
}

void XYGraphicsScene::setGraphicsItemMovePos(QGraphicsItem *item, const QPointF &pos)
{
    switch (meShape)
    {
    case RECT:
    {
        XYRectGraphicsItem *rectItem = static_cast<XYRectGraphicsItem *>(item);
        if (rectItem)
        {
            rectItem->moRect = QRectF(qMin(rectItem->startPos.x(), pos.x()),
                                      qMin(rectItem->startPos.y(), pos.y()),
                                      qAbs(rectItem->startPos.x() - pos.x()),
                                      qAbs(rectItem->startPos.y() - pos.y()));
        }
        break;
    }
    case PATH:
    {
        XYPathGraphicsItem *pathItem = static_cast<XYPathGraphicsItem *>(item);
        if (pathItem)
        {
            pathItem->moPath.lineTo(pos);
        }
        break;
    }
    case ELLIPSE:
    {
        XYEllipseGraphicsItem *rectItem = static_cast<XYEllipseGraphicsItem *>(item);
        if (rectItem)
        {
            rectItem->moRect = QRectF(qMin(rectItem->startPos.x(), pos.x()),
                                      qMin(rectItem->startPos.y(), pos.y()),
                                      qAbs(rectItem->startPos.x() - pos.x()),
                                      qAbs(rectItem->startPos.y() - pos.y()));
        }
        break;
    }
    default:
        break;
    }
}
