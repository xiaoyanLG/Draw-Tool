#include "xymovablewidget.h"
#include <QMouseEvent>

XYMovableWidget::XYMovableWidget(QWidget *parent)
    : QWidget(parent)
{
    mbLeftMousePressed = false;
}

XYMovableWidget::~XYMovableWidget()
{

}

void XYMovableWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mbLeftMousePressed = true;
        moLastPos = event->globalPos();
    }
    QWidget::mousePressEvent(event);
}

void XYMovableWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mbLeftMousePressed = false;
        moLastPos = event->globalPos();
    }
    QWidget::mouseReleaseEvent(event);
}

void XYMovableWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (mbLeftMousePressed && rect().contains(event->pos()))
    {
        QPoint lastpos = pos();
        lastpos.setX( lastpos.x() + event->globalX() - moLastPos.x());
        lastpos.setY( lastpos.y() + event->globalY() - moLastPos.y());
        move(lastpos);
        moLastPos = event->globalPos();
    }
    QWidget::mouseMoveEvent(event);
}

