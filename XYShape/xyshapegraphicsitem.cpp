#include "xyshapegraphicsitem.h"

XYShapeGraphicsItem::XYShapeGraphicsItem(QGraphicsItem *parent)
    : QAbstractGraphicsShapeItem(parent)
{
    creating = true;
}

QRectF XYShapeGraphicsItem::boundingRect() const
{
    return QRectF();
}

void XYShapeGraphicsItem::paint(QPainter *painter,
                                const QStyleOptionGraphicsItem *option,
                                QWidget *)
{
    painter->setRenderHints(QPainter::Antialiasing);
    QPen pen = this->pen();
    paintPen = this->pen();
    if (option->state & QStyle::State_MouseOver
            || creating)
    {
        pen.setColor(QColor("red"));
    }

    painter->setPen(pen);
    painter->setFont(getFont());
    painter->setBrush(brush());
}

bool XYShapeGraphicsItem::isValid()
{
    return true;
}

int XYShapeGraphicsItem::type() const
{
    return XYSHAPE;
}

QPen XYShapeGraphicsItem::getPaintPen() const
{
    return paintPen;
}

QLineF XYShapeGraphicsItem::getEllipseAndLineNodes(qreal k, qreal b, qreal c, qreal d, qreal r)
{
    // 求圆和直线的交点坐标
    // y = kx +b
    // (x+c)^2 + (y+d)^2 = r^2
    qreal temp1 = sqrt((k*k+1)*r*r - c*c*k*k + (2*c*d + 2*b*c)*k - d*d -2*b*d -b*b);
    qreal temp2 = (d+b)*k+c;
    qreal temp3 = k*k + 1;
    qreal x1 = -(temp1 + temp2) / temp3;
    qreal x2 = (temp1 - temp2) / temp3;

    qreal temp4 = sqrt(k*k*r*r + r*r - c*c*k*k + 2*c*d*k + 2*b*c*k - d*d - 2*b*d - b*b);
    qreal y1 = -(k*(c+temp4) +d*k*k-b) / temp3;
    qreal y2 = -(k*(c-temp4) +d*k*k-b) / temp3;

    return QLineF(QPointF(x1, y1), QPointF(x2, y2));
}

QLineF XYShapeGraphicsItem::getVerticalLine(const QPointF &start,
                                            const QPointF &end,
                                            qreal distance,
                                            qreal len)
{
    // 直线方程： y = kx + b
    if (end.y() != start.y() && end.x() != start.x()) // 不垂直X轴
    {
        qreal k = (start.y() - end.y()) / (start.x() - end.x());
        qreal b = start.y() - k * start.x();

        qreal c = -start.x();
        qreal d = -start.y();
        qreal r = distance;
        // 求圆和直线的交点坐标
        QLineF nodes = getEllipseAndLineNodes(k, b, c, d, r);

        qreal x,y; //交点
        if (start.x() > end.x())
        {
            if (nodes.x1() < nodes.x2())
            {
                x = nodes.x1();
                y = nodes.y1();
            }
            else
            {
                x = nodes.x2();
                y = nodes.y2();
            }
        }
        else
        {
            if (nodes.x1() > nodes.x2())
            {
                x = nodes.x1();
                y = nodes.y1();
            }
            else
            {
                x = nodes.x2();
                y = nodes.y2();
            }
        }

        qreal k1 = -1/k;
        qreal b1 = y - k1 * x;
        qreal c1 = -x;
        qreal d1 = -y;
        qreal r1 = len / 2;
        return getEllipseAndLineNodes(k1, b1, c1, d1, r1);
    }
    else
    {
        QLineF line;
        int dire;
        if (end.x() == start.x())
        {
            dire = end.y() > start.y() ? 1:-1;
            line = QLineF(QPointF(start.x() - len / 2, start.y() + (distance * dire)),
                          QPointF(start.x() + len / 2, start.y() + (distance * dire)));
        }
        else
        {
            dire = end.x() > start.x() ? 1:-1;
            line = QLineF(QPointF(start.x() + (distance * dire), start.y() - len / 2),
                          QPointF(start.x() + (distance * dire), start.y() + len / 2));
        }
        return line;
    }
}

QFont XYShapeGraphicsItem::getFont() const
{
    return moFont;
}

void XYShapeGraphicsItem::setFont(const QFont &value)
{
    moFont = value;
}

