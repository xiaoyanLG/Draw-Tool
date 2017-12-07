#include "mainwindow.h"
#include "xygraphicsview.h"
#include "xygraphicsscene.h"
#include "xycanvasgraphicsitem.h"
#include "xyrectgraphicsitem.h"
#include "xypathgraphicsitem.h"
#include "xyellipsegraphicsitem.h"
#include "xypensettingwidget.h"

#include <QToolBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QGraphicsTextItem>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scene = new XYGraphicsScene(0, 0, 700, 500);
    view = new XYGraphicsView(scene);
    scene->setTextEdit(new QTextEdit(view));
    canvas = new XYCanvasGraphicsItem;
    canvas->setZValue(-1);

    view->scene()->setBackgroundBrush(QPixmap(":/backimage.jpg"));

    setCentralWidget(view);

    initToolBar();

    view->installEventFilter(this);
    setAcceptDrops(true);
    connect(scene, SIGNAL(selectItemChanged(QGraphicsItem*)),
            XYPenSettingWidget::getInstance(), SLOT(initWithItem(QGraphicsItem*)));
    connect(XYPenSettingWidget::getInstance(), SIGNAL(penChanged(QPen)),
            scene, SLOT(slotPenChanged(QPen)));
    connect(XYPenSettingWidget::getInstance(), SIGNAL(brushChanged(QBrush)),
            scene, SLOT(slotBrushChanged(QBrush)));
    connect(XYPenSettingWidget::getInstance(), SIGNAL(fontChanged(QFont)),
            scene, SLOT(slotFontChanged(QFont)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::setShape(QAction *act)
{
    if (act)
    {
        scene->setItemMovable(false);
        if (act->text() == "Rect")
        {
            scene->setShape(XYGraphicsScene::RECT);
        }
        else if (act->text() == "Polygon")
        {
            scene->setShape(XYGraphicsScene::POLYGON);
        }
        else if (act->text() == "Path")
        {
            scene->setShape(XYGraphicsScene::PATH);
        }
        else if (act->text() == "Ellipse")
        {
            scene->setShape(XYGraphicsScene::ELLIPSE);
        }
        else if (act->text() == "Line")
        {
            scene->setShape(XYGraphicsScene::LINE);
        }
        else if (act->text() == "Arrows")
        {
            scene->setShape(XYGraphicsScene::ARROWS);
        }
        else if (act->text() == "Text")
        {
            scene->setShape(XYGraphicsScene::TEXT);
        }
        else if (act->text() == "Pixmap")
        {
            scene->setShape(XYGraphicsScene::PIXMAP);
        }
        else if (act->text() == "Cursor")
        {
            scene->setShape(XYGraphicsScene::CURSOR);
            scene->setItemMovable(true);
        }
        else if (act->text() == "Delete")
        {
            scene->setShape(XYGraphicsScene::DELETE);
        }
    }
}

void MainWindow::openPixmap(const QString &path)
{
    if (path.isEmpty())
    {
        lastPixmapPath = QFileDialog::getOpenFileName(this, tr("Open File"),
                                     "",
                                     tr("PNG (*.png);;JPG (*.jpg)"));
    }
    else
    {
        lastPixmapPath = path;
    }
    QPixmap pixmap(lastPixmapPath);
    if (!pixmap.isNull())
    {
        if (canvas->scene())
        {
            canvas->scene()->removeItem(canvas);
        }
        canvas->setPixmap(pixmap);
        scene->setSceneRect(pixmap.rect());
        scene->addItem(canvas);
    }
}

void MainWindow::savePixmap()
{
    QString path = lastPixmapPath;
    if (path.isEmpty())
    {
        path = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                      "untitled.png",
                                                      tr("PNG (*.png);;JPG (*.jpg)"));
    }
    if (!path.isEmpty())
    {
        QPixmap pixmap(scene->sceneRect().width(), scene->sceneRect().height());

        QPainter painter(&pixmap);
        scene->render(&painter);
        if (pixmap.save(path, path.mid(path.lastIndexOf(".") + 1).toUpper().toLocal8Bit().data()))
        {
            lastPixmapPath = path;
        }
    }
}

void MainWindow::settingPen()
{
    XYPenSettingWidget *penSetting = XYPenSettingWidget::getInstance();
    if (penSetting->isHidden())
    {
        penSetting->setVisible(true);
        penSetting->raise();
        penSetting->move(pos().x() + width() + 20,
                         pos().y() + 70);
    }
    else
    {
        penSetting->setVisible(false);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox box;
    box.setIcon(QMessageBox::Question);
    box.setWindowTitle(QStringLiteral("退出确认"));
    box.setText(QStringLiteral("是否需要保存当前图片？"));
    box.addButton(QMessageBox::Yes)->setText(QStringLiteral("是"));
    box.addButton(QMessageBox::No)->setText(QStringLiteral("否"));
    box.addButton(QMessageBox::Ignore)->setText(QStringLiteral("忽略"));
    int ret = box.exec();
    switch (ret) {
    case QMessageBox::Yes:
        savePixmap();
        break;
    case QMessageBox::No:
        event->accept();
        break;
    case QMessageBox::Ignore:
        event->ignore();
        return;
        break;
    default:
        // should never be reached
        break;
    }

    QMainWindow::closeEvent(event);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == view)
    {
        if (event->type() == QEvent::Drop)
        {
            QDropEvent *drag = (QDropEvent *)event;
            const QMimeData *mimeData = drag->mimeData();
            if (mimeData->hasUrls())
            {
                QList<QUrl> urlList = mimeData->urls();
                if (urlList.size() > 1)
                {
                    QMessageBox::warning(this, QStringLiteral("警告"),
                                         QStringLiteral("只能处理一个文件！"));
                    return true;
                }
                else
                {
                    if (scene->getShape() == XYGraphicsScene::PIXMAP)
                    {
                        QString path = urlList.at(0).toLocalFile();
                        scene->addPixmapItem(path, drag->posF());
                    }
                    else
                    {
                        QString path = urlList.at(0).toLocalFile();
                        openPixmap(path);
                    }
                }
            }
            return true;
        }
        else if (event->type() == QEvent::DragEnter)
        {
            QDragEnterEvent *drag = (QDragEnterEvent *)event;
            drag->acceptProposedAction();
            return true;
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::initToolBar()
{
    QToolBar *bar = new QToolBar;
    QActionGroup *shapeGroup = new QActionGroup(this);

    QAction *act = bar->addAction(QIcon(":/open.ico"), QString("Open File"), this, SLOT(openPixmap()));
    act->setToolTip(QStringLiteral("打开图片"));
    act = bar->addAction(QIcon(":/save.ico"), QString("Save File"), this, SLOT(savePixmap()));
    act->setToolTip(QStringLiteral("保存图片"));
    act = bar->addAction(QIcon(":/cursor.ico"), QString("Cursor"));
    act->setToolTip(QStringLiteral("移动图元"));
    act->setCheckable(true);
    act->setChecked(true);
    scene->setShape(XYGraphicsScene::CURSOR);
    shapeGroup->addAction(act);
    act = bar->addAction(QIcon(":/rect.ico"), QString("Rect"));
    act->setToolTip(QStringLiteral("绘制矩形"));
    act->setCheckable(true);
    shapeGroup->addAction(act);
    act = bar->addAction(QIcon(":/polygon.ico"), QString("Polygon"));
    act->setToolTip(QStringLiteral("绘制多边形"));
    act->setCheckable(true);
    shapeGroup->addAction(act);
    act = bar->addAction(QIcon(":/ellipse.ico"), QString("Ellipse"));
    act->setToolTip(QStringLiteral("绘制椭圆"));
    act->setCheckable(true);
    shapeGroup->addAction(act);
    act = bar->addAction(QIcon(":/arrows.ico"), QString("Arrows"));
    act->setToolTip(QStringLiteral("绘制箭头"));
    act->setCheckable(true);
    shapeGroup->addAction(act);
    act = bar->addAction(QIcon(":/line.ico"), QString("Line"));
    act->setToolTip(QStringLiteral("绘制直线"));
    act->setCheckable(true);
    shapeGroup->addAction(act);
    act = bar->addAction(QIcon(":/draw.ico"), QString("Path"));
    act->setToolTip(QStringLiteral("绘制自定义曲线"));
    act->setCheckable(true);
    shapeGroup->addAction(act);
    act = bar->addAction(QIcon(":/text.ico"), QString("Text"));
    act->setToolTip(QStringLiteral("绘制文本"));
    act->setCheckable(true);
    shapeGroup->addAction(act);
    act = bar->addAction(QIcon(":/pixmap.ico"), QString("Pixmap"));
    act->setToolTip(QStringLiteral("插入图片模式下，直接拖拽图片进入窗口即可！"));
    act->setCheckable(true);
    shapeGroup->addAction(act);
    act = bar->addAction(QIcon(":/stick.ico"), QString("Stick"),
                         scene, SLOT(stickItem()));
    act->setToolTip(QStringLiteral("图元置顶"));
    act = bar->addAction(QIcon(":/zoomup.ico"), QString("Zoom Up"),
                         scene, SLOT(zoomUpItem()));
    act->setAutoRepeat(true);
    act->setShortcut(QKeySequence(tr("Ctrl+U")));
    act->setToolTip(QStringLiteral("放大图元"));
    act = bar->addAction(QIcon(":/zoomdown.ico"), QString("Zoom Down"),
                         scene, SLOT(zoomDownItem()));
    act->setAutoRepeat(true);
    act->setShortcut(QKeySequence(tr("Ctrl+D")));
    act->setToolTip(QStringLiteral("缩小图元"));
    act = bar->addAction(QIcon(":/rotation.ico"), QString("Rotation"),
                         scene, SLOT(rotationItem()));
    act->setAutoRepeat(true);
    act->setShortcut(QKeySequence(tr("Ctrl+R")));
    act->setToolTip(QStringLiteral("旋转图元"));
    act = bar->addAction(QIcon(":/settingpen.ico"), QString("SettingPen"),
                         this, SLOT(settingPen()));
    act->setToolTip(QStringLiteral("设置画笔画刷字体"));
    act = bar->addAction(QIcon(":/delete.ico"), QString("Delete"));
    act->setToolTip(QStringLiteral("删除图元"));
    act->setCheckable(true);
    shapeGroup->addAction(act);

    connect(shapeGroup, SIGNAL(triggered(QAction *)),
            this, SLOT(setShape(QAction *)));

    addToolBar(bar);
}
