#include "xygraphicsscene.h"
#include "xyrectgraphicsitem.h"
#include "xypathgraphicsitem.h"
#include "xyellipsegraphicsitem.h"
#include "xylinegraphicsitem.h"
#include "xyarrowsgraphicsitem.h"

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

void XYGraphicsScene::setItemMovable(bool movable)
{
    XYMovableGraphicsItem::acceptMouse = movable;
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
    static XYShapeGraphicsItem *item = NULL;
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
                setGraphicsItemEndPos(item, mouse_event->scenePos());
                this->removeItem(item);
                if (item->isValid())
                {
                    this->addItem(item);
                }
                else
                {
                    delete item;
                }
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

XYShapeGraphicsItem *XYGraphicsScene::getCurDrawshapeItem()
{
    XYShapeGraphicsItem *item = NULL;
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
    case LINE:
        item = new XYLineGraphicsItem;
        break;
    case ARROWS:
        item = new XYArrowsGraphicsItem;
        break;
    default:
        break;
    }

    return item;
}

void XYGraphicsScene::setGraphicsItemStartPos(XYShapeGraphicsItem *item, const QPointF &pos)
{
    switch (meShape)
    {
    case PATH:
    {
        XYPathGraphicsItem *pathItem = static_cast<XYPathGraphicsItem *>(item);
        if (pathItem)
        {
            pathItem->moPath.moveTo(pos);
        }
        break;
    }
    case RECT:
    case ELLIPSE:
    case LINE:
        break;
    case ARROWS:
    {
        XYArrowsGraphicsItem *arrowsItem = static_cast<XYArrowsGraphicsItem *>(item);
        arrowsItem->endPos = pos;
        break;
    }
    default:
        break;
    }
    XYMovableGraphicsItem *moveItem = static_cast<XYMovableGraphicsItem *>(item);
    if (moveItem)
    {
        moveItem->startPos = pos;
    }
}

void XYGraphicsScene::setGraphicsItemEndPos(XYShapeGraphicsItem *item, const QPointF &pos)
{
    XYMovableGraphicsItem *moveItem = static_cast<XYMovableGraphicsItem *>(item);
    if (moveItem)
    {
        moveItem->endPos = pos;
    }
}

void XYGraphicsScene::setGraphicsItemMovePos(XYShapeGraphicsItem *item, const QPointF &pos)
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
        XYEllipseGraphicsItem *ellipseItem = static_cast<XYEllipseGraphicsItem *>(item);
        if (ellipseItem)
        {
            ellipseItem->moRect = QRectF(qMin(ellipseItem->startPos.x(), pos.x()),
                                      qMin(ellipseItem->startPos.y(), pos.y()),
                                      qAbs(ellipseItem->startPos.x() - pos.x()),
                                      qAbs(ellipseItem->startPos.y() - pos.y()));
        }
        break;
    }
    case LINE:
    {
        XYLineGraphicsItem *lineItem = static_cast<XYLineGraphicsItem *>(item);
        if (lineItem)
        {
            lineItem->moLine = QLineF(lineItem->startPos, pos);
        }
        break;
    }
    case ARROWS:
    {
        XYArrowsGraphicsItem *arrowsItem = static_cast<XYArrowsGraphicsItem *>(item);
        if (arrowsItem)
        {
            arrowsItem->endPos = pos;
        }
        break;
    }
    default:
        break;
    }
}
