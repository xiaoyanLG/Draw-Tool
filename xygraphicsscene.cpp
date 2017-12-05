#include "xygraphicsscene.h"
#include "xycanvasgraphicsitem.h"
#include "xyrectgraphicsitem.h"
#include "xypathgraphicsitem.h"
#include "xyellipsegraphicsitem.h"
#include "xylinegraphicsitem.h"
#include "xyarrowsgraphicsitem.h"
#include "xytextgraphicsitem.h"
#include "xypixmapgraphicsitem.h"
#include "xypensettingwidget.h"
#include <QGraphicsView>
#include <QApplication>

XYGraphicsScene::XYGraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent)
    : QGraphicsScene(x, y, width, height, parent)
{
    meShape = CURSOR;
    haveKeyboardItem = NULL;
    selectItem = NULL;
    textEdit = NULL;
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

void XYGraphicsScene::setTextEdit(QTextEdit *textEdit)
{
    this->textEdit = textEdit;
    if (this->textEdit != NULL)
    {
        this->textEdit->setVisible(false);
        connect(this->textEdit, SIGNAL(textChanged()), this, SLOT(setItemText()));
    }
}

void XYGraphicsScene::addPixmapItem(const QString &file, const QPointF &pos)
{
    QPixmap pixmap(file);
    if (!pixmap.isNull())
    {
        XYPixmapGraphicsItem *item = new XYPixmapGraphicsItem(pixmap);
        item->setPos(pos - QPointF(pixmap.width() / 2, pixmap.height()));
        this->addItem(item);
    }
}

void XYGraphicsScene::savePixmap(const QString &path)
{
    QPixmap pixmap;
    QPainter painter(&pixmap);
    this->render(&painter);
    pixmap.save(path);
}

void XYGraphicsScene::showTextEdit(XYTextGraphicsItem *item)
{
    if (textEdit != NULL)
    {
        haveKeyboardItem = item;
        qreal x_offset = 0;
        qreal y_offset = 0;
        if (!views().isEmpty())
        {
            x_offset = views().at(0)->width();
            y_offset = views().at(0)->height();
        }
        if (x_offset > width())
        {
            x_offset = (x_offset - width()) / 2;
        }
        if (y_offset > height())
        {
            y_offset = (y_offset - height()) / 2;
        }
        x_offset = x_offset * item->scale();
        y_offset = y_offset * item->scale();
        textEdit->resize(item->sceneBoundingRect().width(),
                         item->sceneBoundingRect().height());
        textEdit->move(item->sceneBoundingRect().x() + x_offset,
                       item->sceneBoundingRect().y() + y_offset);
        textEdit->setText(((XYTextGraphicsItem *)item)->msText);
        textEdit->setFocus();
        textEdit->setVisible(true);
    }
}

void XYGraphicsScene::stickItem()
{
    static int z = 1;
    if (selectItem)
    {
        selectItem->setZValue(z++);
    }
}

void XYGraphicsScene::zoomUpItem()
{
    if (selectItem)
    {
        if (textEdit != NULL && !textEdit->isHidden())
        {
            textEdit->setVisible(false);
        }
        selectItem->setScale(selectItem->scale() + 0.02);
    }
}

void XYGraphicsScene::zoomDownItem()
{
    if (selectItem)
    {
        if (textEdit != NULL && !textEdit->isHidden())
        {
            textEdit->setVisible(false);
        }
        qreal cur = selectItem->scale() - 0.02;
        if (cur < 0)
        {
            cur = 0;
        }
        selectItem->setScale(cur);
    }
}

void XYGraphicsScene::setItemText()
{
    if (textEdit != NULL && haveKeyboardItem != NULL)
    {
        ((XYTextGraphicsItem *)haveKeyboardItem)->msText = textEdit->toPlainText();
    }
}

void XYGraphicsScene::slotPenChanged(const QPen &pen)
{
    if (selectItem != NULL
            && (selectItem->type() == XYMovableGraphicsItem::XYSHAPE
                || selectItem->type() == XYMovableGraphicsItem::XYSHAPEMOVABLE
                || selectItem->type() == XYMovableGraphicsItem::XYTEXT))
    {
        XYShapeGraphicsItem *item = (XYShapeGraphicsItem *)selectItem;
        item->setPen(pen);
    }
}

void XYGraphicsScene::slotBrushChanged(const QBrush &brush)
{
    if (selectItem != NULL
            && (selectItem->type() == XYMovableGraphicsItem::XYSHAPE
                || selectItem->type() == XYMovableGraphicsItem::XYSHAPEMOVABLE
                || selectItem->type() == XYMovableGraphicsItem::XYTEXT))
    {
        XYShapeGraphicsItem *item = (XYShapeGraphicsItem *)selectItem;
        item->setBrush(brush);
    }
}

void XYGraphicsScene::slotFontChanged(const QFont &font)
{
    if (textEdit != NULL && !textEdit->isHidden())
    {
        textEdit->setFont(font);
    }
    if (selectItem != NULL
            && (selectItem->type() == XYMovableGraphicsItem::XYSHAPE
                || selectItem->type() == XYMovableGraphicsItem::XYSHAPEMOVABLE
                || selectItem->type() == XYMovableGraphicsItem::XYTEXT))
    {
        XYShapeGraphicsItem *item = (XYShapeGraphicsItem *)selectItem;
        item->setFont(font);
    }
}

bool XYGraphicsScene::event(QEvent *event)
{
    static XYMovableGraphicsItem *item = NULL;
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
        event->accept();
    }
    else if (event->type() == QEvent::GraphicsSceneMouseRelease)
    {
        if (mouse_event->button() == Qt::LeftButton)
        {
            if (item)
            {
                setGraphicsItemMovePos(item, mouse_event->scenePos());
                this->removeItem(item);
                if (item->isValid())
                {
                    this->addItem(item);
                    setGraphicsItemEndPos(item, mouse_event->scenePos());
                    if (selectItem != NULL
                            && (selectItem->type() == XYMovableGraphicsItem::XYSHAPE
                                || selectItem->type() == XYMovableGraphicsItem::XYSHAPEMOVABLE
                                || selectItem->type() == XYMovableGraphicsItem::XYTEXT))
                    {
                        ((XYMovableGraphicsItem *)selectItem)->selected = false;
                    }
                    selectItem = item;
                }
                else
                {
                    delete item;
                }
                item = NULL;
            }
        }
        event->accept();
    }
    else if (event->type() == QEvent::GraphicsSceneMouseMove)
    {
        if (item)
        {
            setGraphicsItemMovePos(item, mouse_event->scenePos());
            update(this->sceneRect());
        }
        event->accept();
    }
    return true;
}

void XYGraphicsScene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    if (selectItem != NULL)
    {
        if (event->delta() > 0)
        {
            zoomUpItem();
        }
        else
        {
            zoomDownItem();
        }
        event->accept();
    }
}

void XYGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
    {
        QList<QGraphicsItem *> items = this->items();
        for (int i = 0; i < items.size(); ++i)
        {
            if (((XYMovableGraphicsItem *)items.at(i))->selected)
            {
                ((XYMovableGraphicsItem *)items.at(i))->mouseMoveEvent(mouseEvent);
            }
        }
    }
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void XYGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsItem *item = itemAt(mouseEvent->scenePos(), QTransform());
    if (item != NULL && item->type() == XYCanvasGraphicsItem::XYCANVAS)
    {
        item = NULL;
    }

    if (selectItem != item)
    {
        emit selectItemChanged(item);
    }
    selectItem = item;

    switch (meShape)
    {
    case DELETE:
        if (item != NULL)
        {
            removeItem(item);
            delete item;
            selectItem = NULL;
        }
        return;
    default:
        break;
    }

    if (textEdit != NULL && !textEdit->isHidden())
    {
        textEdit->setVisible(false);
    }

    // 去掉非点击item选中
    QList<QGraphicsItem *> items = this->items();
    for (int i = 0; i < items.size(); ++i)
    {
        switch (items.at(i)->type())
        {
        case XYMovableGraphicsItem::XYSHAPE:
        case XYMovableGraphicsItem::XYSHAPEMOVABLE:
        case XYMovableGraphicsItem::XYTEXT:
            if (items.at(i) != item)
            {
                ((XYMovableGraphicsItem *)items.at(i))->selected = false;
            }
            else if (items.at(i) == item)
            {
                ((XYMovableGraphicsItem *)items.at(i))->selected = true;
            }

        break;
        case XYCanvasGraphicsItem::XYCANVAS:
            break;
        default:
            break;
        }
    }
    update(sceneRect());
    QGraphicsScene::mousePressEvent(mouseEvent);
}

QPen XYGraphicsScene::getCurPen()
{
    XYPenSettingWidget *penSetting = XYPenSettingWidget::getInstance();
    return penSetting->getMoPen();
}

QFont XYGraphicsScene::getCurFont()
{
    XYPenSettingWidget *penSetting = XYPenSettingWidget::getInstance();
    return penSetting->getMoFont();
}

QBrush XYGraphicsScene::getCurBrush()
{
    XYPenSettingWidget *penSetting = XYPenSettingWidget::getInstance();
    return penSetting->getMoBrush();
}

XYMovableGraphicsItem *XYGraphicsScene::getCurDrawshapeItem()
{
    XYMovableGraphicsItem *item = NULL;
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
    case TEXT:
        item = new XYTextGraphicsItem;
        if (textEdit != NULL)
        {
            textEdit->setTextColor(getCurPen().color());
            textEdit->setFont(getCurFont());
        }
        break;
    case PIXMAP:
        break;
    default:
        break;
    }

    if (item != NULL)
    {
        item->setPen(getCurPen());
        item->setFont(getCurFont());
        item->setBrush(getCurBrush());
    }
    return item;
}

void XYGraphicsScene::setGraphicsItemStartPos(XYMovableGraphicsItem *item, const QPointF &pos)
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
    case TEXT:
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
        moveItem->startCreateItem(pos);
    }
}

void XYGraphicsScene::setGraphicsItemEndPos(XYMovableGraphicsItem *item, const QPointF &pos)
{
    XYMovableGraphicsItem *moveItem = static_cast<XYMovableGraphicsItem *>(item);
    if (moveItem)
    {
        moveItem->endCreateItem(pos);
    }
}

void XYGraphicsScene::setGraphicsItemMovePos(XYMovableGraphicsItem *item, const QPointF &pos)
{
    item->endPos = pos;
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
    case TEXT:
    {
        XYMovableGraphicsItem *generalItem = static_cast<XYMovableGraphicsItem *>(item);
        if (generalItem)
        {
            generalItem->duringCreateItem(pos);
        }
        break;
    }
    default:
        break;
    }
}
