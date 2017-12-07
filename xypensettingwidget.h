#ifndef XYPENSETTINGWIDGET_H
#define XYPENSETTINGWIDGET_H

#include "xymovablewidget.h"
#include <QPen>
#include <QLabel>
#include <QComboBox>
#include <QFontComboBox>
#include <QSlider>
#include <QGroupBox>
#include <QGridLayout>
#include <QColorDialog>
#include <QMouseEvent>
#include <QPainter>
#include <QGraphicsItem>

class XYLabel: public QLabel
{
    Q_OBJECT
public:
    XYLabel(const QColor &color = QColor(), QWidget *parent = 0);

    QColor getColor() const;
    void setColor(const QColor &value);
    QSize sizeHint() const;

signals:
    void selectColor();
    void colorChanged(const QColor &color);

public slots:
    void mslotSelectColor();

protected:
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QColor color;
};

class XYPenSettingWidget : public XYMovableWidget
{
    Q_OBJECT
public:
    static XYPenSettingWidget *getInstance();
    explicit XYPenSettingWidget(QWidget *parent = 0);
    ~XYPenSettingWidget();

    QPen getMoPen();
    void setMoPen(const QPen &value);

    QFont getMoFont();
    void setMoFont(const QFont &value);

    QBrush getMoBrush();
    void setMoBrush(const QBrush &value);

signals:
    void penChanged(const QPen &pen);
    void brushChanged(const QBrush &brush);
    void fontChanged(const QFont &font);

public slots:
    void slotPenChanged();
    void slotBrushChanged();
    void slotFontChanged();
    void initWithItem(QGraphicsItem *selectItem);

private:
    QPen moPen;
    QBrush moBrush;
    QFont moFont;

    XYLabel *selectPenColor;
    QComboBox *selectPenStyle;
    QSlider *penOpacityBox;
    QSlider *widthBox;

    XYLabel *selectBrushColor;
    QComboBox *selectBrushStyle;
    QSlider *brushOpacityBox;

    QFontComboBox *selectFonts;
    QSlider *sizeBox;

    bool  emitSignal;

};

#endif // XYPENSETTINGWIDGET_H
