#include "xypensettingwidget.h"
#include "xymovablegraphicsitem.h"

XYPenSettingWidget *XYPenSettingWidget::getInstance()
{
    static XYPenSettingWidget *instance = NULL;
    if (instance == NULL)
    {
        instance = new XYPenSettingWidget;
    }
    return instance;
}

XYPenSettingWidget::XYPenSettingWidget(QWidget *parent)
    : XYMovableWidget(parent), emitSignal(true)
{
    this->setWindowFlags(Qt::FramelessWindowHint
                         | Qt::WindowType_Mask);

#define ADDITEM(instance, value) instance->addItem(#value, (int)value)
    int row = 0;
    QLabel *penColor = new QLabel(QStringLiteral("画笔颜色"));
    selectPenColor = new XYLabel(QColor("green"));
    connect(selectPenColor, SIGNAL(colorChanged(QColor)), this, SLOT(slotPenChanged()));
    QLabel *penStyle = new QLabel(QStringLiteral("画笔风格"));
    selectPenStyle = new QComboBox;
    ADDITEM(selectPenStyle, Qt::SolidLine);
    ADDITEM(selectPenStyle, Qt::DashLine);
    ADDITEM(selectPenStyle, Qt::DotLine);
    ADDITEM(selectPenStyle, Qt::DashDotLine);
    ADDITEM(selectPenStyle, Qt::DashDotDotLine);
    ADDITEM(selectPenStyle, Qt::NoPen);
    connect(selectPenStyle, SIGNAL(currentIndexChanged(int)), this, SLOT(slotPenChanged()));
    QLabel *penOpacity = new QLabel(QStringLiteral("画笔透明度"));
    penOpacityBox = new QSlider;
    penOpacityBox->setOrientation(Qt::Horizontal);
    penOpacityBox->setMinimum(0);
    penOpacityBox->setMaximum(255);
    penOpacityBox->setValue(0);
    connect(penOpacityBox, SIGNAL(valueChanged(int)), this, SLOT(slotPenChanged()));
    QLabel *penWidth = new QLabel(QStringLiteral("画笔宽度"));
    widthBox = new QSlider;
    widthBox->setOrientation(Qt::Horizontal);
    widthBox->setMinimum(1);
    widthBox->setMaximum(50);
    widthBox->setValue(1);
    connect(widthBox, SIGNAL(valueChanged(int)), this, SLOT(slotPenChanged()));
    QGroupBox *penBox = new QGroupBox(QStringLiteral("画笔设置"));
    QGridLayout *penLayout = new QGridLayout(penBox);
    row = 0;
    penLayout->addWidget(penColor, row, 0);
    penLayout->addWidget(selectPenColor, row++, 1);
    penLayout->addWidget(penStyle, row, 0);
    penLayout->addWidget(selectPenStyle, row++, 1);
    penLayout->addWidget(penOpacity, row, 0);
    penLayout->addWidget(penOpacityBox, row++, 1);
    penLayout->addWidget(penWidth, row, 0);
    penLayout->addWidget(widthBox, row++, 1);

    QLabel *brushColor = new QLabel(QStringLiteral("画刷颜色"));
    selectBrushColor = new XYLabel(QColor("green"));
    connect(selectBrushColor, SIGNAL(colorChanged(QColor)), this, SLOT(slotBrushChanged()));
    QLabel *brushStyle = new QLabel(QStringLiteral("画刷风格"));
    selectBrushStyle = new QComboBox;
    ADDITEM(selectBrushStyle, Qt::SolidPattern);
    ADDITEM(selectBrushStyle, Qt::Dense1Pattern);
    ADDITEM(selectBrushStyle, Qt::HorPattern);
    ADDITEM(selectBrushStyle, Qt::VerPattern);
    ADDITEM(selectBrushStyle, Qt::CrossPattern);
    ADDITEM(selectBrushStyle, Qt::BDiagPattern);
    ADDITEM(selectBrushStyle, Qt::FDiagPattern);
    ADDITEM(selectBrushStyle, Qt::DiagCrossPattern);
    ADDITEM(selectBrushStyle, Qt::NoBrush);
    connect(selectBrushStyle, SIGNAL(currentIndexChanged(int)), this, SLOT(slotBrushChanged()));
    QLabel *brushOpacity = new QLabel(QStringLiteral("画刷透明度"));
    brushOpacityBox = new QSlider;
    brushOpacityBox->setOrientation(Qt::Horizontal);
    brushOpacityBox->setMinimum(0);
    brushOpacityBox->setMaximum(255);
    brushOpacityBox->setValue(0);
    connect(brushOpacityBox, SIGNAL(valueChanged(int)), this, SLOT(slotBrushChanged()));
    QGroupBox *brushBox = new QGroupBox(QStringLiteral("画刷设置"));
    QGridLayout *brushLayout = new QGridLayout(brushBox);
    row = 0;
    brushLayout->addWidget(brushColor, row, 0);
    brushLayout->addWidget(selectBrushColor, row++, 1);
    brushLayout->addWidget(brushStyle, row, 0);
    brushLayout->addWidget(selectBrushStyle, row++, 1);
    brushLayout->addWidget(brushOpacity, row, 0);
    brushLayout->addWidget(brushOpacityBox, row++, 1);

    QLabel *fontFamily = new QLabel(QStringLiteral("字体"));
    selectFonts = new QFontComboBox;
    connect(selectFonts, SIGNAL(currentFontChanged(QFont)), this, SLOT(slotFontChanged()));
    QLabel *fontSize = new QLabel(QStringLiteral("字体大小"));
    sizeBox = new QSlider;
    sizeBox->setOrientation(Qt::Horizontal);
    sizeBox->setMinimum(1);
    sizeBox->setMaximum(100);
    sizeBox->setValue(15);
    connect(sizeBox, SIGNAL(valueChanged(int)), this, SLOT(slotFontChanged()));
    QGroupBox *fontBox = new QGroupBox(QStringLiteral("字体设置"));
    QGridLayout *fontLayout = new QGridLayout(fontBox);
    row = 0;
    fontLayout->addWidget(fontFamily, row, 0);
    fontLayout->addWidget(selectFonts, row++, 1);
    fontLayout->addWidget(fontSize, row, 0);
    fontLayout->addWidget(sizeBox, row++, 1);

    QVBoxLayout *mainlayout = new QVBoxLayout(this);
    mainlayout->addWidget(penBox);
    mainlayout->addWidget(brushBox);
    mainlayout->addWidget(fontBox);
}

XYPenSettingWidget::~XYPenSettingWidget()
{

}
QPen XYPenSettingWidget::getMoPen()
{
    QColor color = selectPenColor->getColor();
    color.setAlpha(255 - penOpacityBox->value());
    moPen.setColor(color);
    moPen.setStyle((Qt::PenStyle)selectPenStyle->currentData().toInt());
    moPen.setWidth(widthBox->value());
    return moPen;
}

void XYPenSettingWidget::setMoPen(const QPen &value)
{
    moPen = value;
    QColor color = moPen.color();
    selectPenColor->setColor(color);
    penOpacityBox->setValue(255 - color.alpha());
    selectPenStyle->setCurrentIndex(selectPenStyle->findData((int)moPen.style()));
    widthBox->setValue(moPen.width());
}
QFont XYPenSettingWidget::getMoFont()
{
    moFont = selectFonts->currentFont();
    moFont.setPixelSize(sizeBox->value());
    return moFont;
}

void XYPenSettingWidget::setMoFont(const QFont &value)
{
    moFont = value;
    selectFonts->setCurrentFont(moFont);
    sizeBox->setValue(moFont.pixelSize());
}
QBrush XYPenSettingWidget::getMoBrush()
{
    QColor color = selectBrushColor->getColor();
    color.setAlpha(255 - brushOpacityBox->value());
    moBrush.setStyle((Qt::BrushStyle)selectBrushStyle->currentData().toInt());
    moBrush.setColor(color);
    return moBrush;
}

void XYPenSettingWidget::setMoBrush(const QBrush &value)
{
    moBrush = value;
    QColor color = moBrush.color();
    brushOpacityBox->setValue(255 - color.alpha());
    selectBrushColor->setColor(color);
    selectBrushStyle->setCurrentIndex(selectBrushStyle->findData((int)moBrush.style()));
}

void XYPenSettingWidget::slotPenChanged()
{
    getMoPen();
    if (emitSignal)
    {
        emit penChanged(moPen);
    }
}

void XYPenSettingWidget::slotBrushChanged()
{
    getMoBrush();
    if (emitSignal)
    {
        emit brushChanged(moBrush);
    }
}

void XYPenSettingWidget::slotFontChanged()
{
    getMoFont();
    if (emitSignal)
    {
        emit fontChanged(moFont);
    }
}

void XYPenSettingWidget::initWithItem(QGraphicsItem *selectItem)
{
    if (selectItem != NULL
            && (selectItem->type() == XYMovableGraphicsItem::XYSHAPE
                || selectItem->type() == XYMovableGraphicsItem::XYSHAPEMOVABLE
                || selectItem->type() == XYMovableGraphicsItem::XYTEXT))
    {
        XYShapeGraphicsItem *item = (XYShapeGraphicsItem *)selectItem;
        emitSignal = false;
        setMoPen(item->getPaintPen());
        setMoBrush(item->brush());
        setMoFont(item->getFont());
        emitSignal = true;
    }
}

void XYLabel::mslotSelectColor()
{
    color = QColorDialog::getColor();
    emit colorChanged(color);
    update();
}

void XYLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QColor(0, 0, 0, 0));
    painter.setBrush(color);
    painter.drawRect(rect());
}

void XYLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if (rect().contains(event->pos()))
    {
        emit selectColor();
    }
}
XYLabel::XYLabel(const QColor &color, QWidget *parent)
    :QLabel(parent), color(color)
{
    setMaximumHeight(25);
    connect(this, SIGNAL(selectColor()), this, SLOT(mslotSelectColor()));
}

QColor XYLabel::getColor() const
{
    return color;
}

void XYLabel::setColor(const QColor &value)
{
    color = value;
    update();
}

QSize XYLabel::sizeHint() const
{
    return QSize(50, 25);
}

